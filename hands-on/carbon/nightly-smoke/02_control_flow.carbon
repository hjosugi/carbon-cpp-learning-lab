import Core library "io";

fn SumTo(limit: i32) -> i32 {
  var sum: i32 = 0;
  var current: i32 = 1;
  while (current <= limit) {
    sum += current;
    ++current;
  }
  return sum;
}

fn Run() {
  Core.Print(SumTo(10));
}
