CXX ?= g++
CPPFLAGS := -Iinclude
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wshadow
SOURCES := src/parser.cpp src/aggregator.cpp src/input.cpp src/c_api.cpp

.PHONY: all release debug test integration sanitize fuzz benchmark warnings clean

all: release

release: build/release/loglens

debug: build/debug/loglens

build/release/loglens: $(SOURCES) src/main.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O3 -DNDEBUG $^ -o $@

build/debug/loglens: $(SOURCES) src/main.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O0 -g3 $^ -o $@

build/test/loglens_tests: $(SOURCES) tests/test_main.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O2 $^ -o $@

test: build/test/loglens_tests
	./build/test/loglens_tests
	$(MAKE) integration

integration: build/debug/loglens
	bash tests/integration.sh ./build/debug/loglens

sanitize:
	@mkdir -p build/sanitize
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O1 -g3 -fno-omit-frame-pointer \
		-fsanitize=address,undefined $(SOURCES) tests/test_main.cpp \
		-o build/sanitize/loglens_tests
	ASAN_OPTIONS=detect_leaks=$${ASAN_DETECT_LEAKS:-0} ./build/sanitize/loglens_tests

fuzz:
	@rm -rf build/fuzz/corpus
	@mkdir -p build/fuzz/corpus
	@cp -R tests/corpus/. build/fuzz/corpus/
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O1 -g3 -fno-omit-frame-pointer \
		-fsanitize=fuzzer,address,undefined src/parser.cpp tests/fuzz_parser.cpp \
		-o build/fuzz/fuzz_parser
	./build/fuzz/fuzz_parser -runs=10000 build/fuzz/corpus

build/benchmark/generate: bench/generate.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -O3 -DNDEBUG $< -o $@

benchmark: build/benchmark/generate build/release/loglens
	./build/benchmark/generate 100000 1000 | ./build/release/loglens --input - >/dev/null

warnings:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Werror -fsyntax-only $(SOURCES) src/main.cpp

clean:
	rm -rf build
