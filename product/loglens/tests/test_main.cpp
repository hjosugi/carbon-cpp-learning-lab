#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "loglens/aggregator.hpp"
#include "loglens/c_api.h"
#include "loglens/input.hpp"
#include "loglens/parser.hpp"

namespace {

auto check(bool condition, const char* expression, int line) -> void {
  if (!condition) {
    std::cerr << "FAIL line " << line << ": " << expression << '\n';
    std::exit(1);
  }
}

#define CHECK(expression) check((expression), #expression, __LINE__)

auto test_parser_accepts_valid_line() -> void {
  const auto result = loglens::parse_line(
      "2026-07-12T01:00:00Z INFO payments-api 17 200");
  CHECK(result.has_value());
  CHECK(result->service == "payments-api");
  CHECK(result->latency_ms == 17);
  CHECK(result->status == 200);
}

auto test_parser_rejects_bad_input() -> void {
  CHECK(!loglens::parse_line("too few fields"));
  CHECK(!loglens::parse_line(
      "2026-07-12T01:00:00Z INFO bad/service 17 200"));
  CHECK(!loglens::parse_line(
      "2026-07-12T01:00:00Z INFO api nope 200"));
  CHECK(!loglens::parse_line(
      "2026-07-12T01:00:00Z INFO api 17 999"));
  CHECK(!loglens::parse_line(
      "2026-02-29T01:00:00Z INFO api 17 200"));
  CHECK(!loglens::parse_line(
      "2024-04-31T01:00:00Z INFO api 17 200"));
  CHECK(!loglens::parse_line(
      "2024-01-01T24:00:00Z INFO api 17 200"));
  CHECK(!loglens::parse_line(
      "2024-01-01T23:59:60Z INFO api 17 200"));
  CHECK(!loglens::parse_line(
      "2024-01-01T23:59:59.Z INFO api 17 200"));
  CHECK(loglens::parse_line(
            "2024-02-29T23:59:59.123456Z INFO api 17 200")
            .has_value());
  CHECK(!loglens::parse_line(
      "2026-07-12T01:00:00Z INFO api 4294967296 200"));
}

auto test_histogram() -> void {
  loglens::LatencyHistogram histogram;
  histogram.add(0);
  histogram.add(1);
  histogram.add(2);
  histogram.add(3);
  histogram.add(8);
  CHECK(histogram.count() == 5);
  CHECK(histogram.percentile_upper(0.0) == 0);
  CHECK(histogram.percentile_upper(0.5) == 3);
  CHECK(histogram.percentile_upper(1.0) == 15);
  CHECK(loglens_bucket_upper(0) == 0);
  CHECK(loglens_bucket_upper(1) == 1);
  CHECK(loglens_bucket_upper(31) == 2147483647ULL);
  CHECK(loglens_bucket_upper(32) == 4294967295ULL);
}

auto test_aggregation_and_json() -> void {
  loglens::Aggregator aggregator;
  const auto first = loglens::parse_line(
      "2026-07-12T01:00:00Z INFO api 10 200");
  const auto second = loglens::parse_line(
      "2026-07-12T01:00:01Z ERROR api 20 500");
  CHECK(first && second);
  CHECK(aggregator.add(*first) == loglens::Aggregator::AddResult::added);
  CHECK(aggregator.add(*second) == loglens::Aggregator::AddResult::added);
  aggregator.add_malformed();

  CHECK(aggregator.accepted() == 2);
  CHECK(aggregator.malformed() == 1);
  const auto& stats = aggregator.services().at("api");
  CHECK(stats.count == 2);
  CHECK(stats.latency_sum == 30);
  CHECK(stats.latency_max == 20);
  CHECK(stats.status_classes[2] == 1);
  CHECK(stats.status_classes[5] == 1);

  const std::string json = loglens::render_json(aggregator);
  CHECK(json.find("\"schema_version\": 1") != std::string::npos);
  CHECK(json.find("\"accepted\": 2") != std::string::npos);
  CHECK(json.find("\"service\": \"api\"") != std::string::npos);
}

auto test_service_limit() -> void {
  loglens::Aggregator aggregator(1);
  const auto first = loglens::parse_line(
      "2026-07-12T01:00:00Z INFO api 10 200");
  const auto second = loglens::parse_line(
      "2026-07-12T01:00:01Z INFO worker 20 200");
  CHECK(first && second);
  CHECK(aggregator.add(*first) == loglens::Aggregator::AddResult::added);
  CHECK(aggregator.add(*first) == loglens::Aggregator::AddResult::added);
  CHECK(aggregator.add(*second) ==
        loglens::Aggregator::AddResult::service_limit_exceeded);
  CHECK(aggregator.accepted() == 2);
  CHECK(aggregator.services().size() == 1);
}

auto test_bounded_reader() -> void {
  std::istringstream input("abc\r\n12345\nlast");
  std::string line;
  CHECK(loglens::read_bounded_line(input, line, 4) ==
        loglens::ReadLineResult::line);
  CHECK(line == "abc");
  CHECK(loglens::read_bounded_line(input, line, 4) ==
        loglens::ReadLineResult::too_long);
  CHECK(line.empty());
  CHECK(loglens::read_bounded_line(input, line, 4) ==
        loglens::ReadLineResult::line);
  CHECK(line == "last");
  CHECK(loglens::read_bounded_line(input, line, 4) ==
        loglens::ReadLineResult::end);
}

}  // namespace

auto main() -> int {
  test_parser_accepts_valid_line();
  test_parser_rejects_bad_input();
  test_histogram();
  test_aggregation_and_json();
  test_service_limit();
  test_bounded_reader();
  std::cout << "All tests passed\n";
  return 0;
}
