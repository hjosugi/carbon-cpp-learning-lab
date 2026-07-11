import Core library "io";

// Pure migration seam. This intentionally avoids I/O and container APIs.
fn BucketUpper(bucket: i32) -> i64 {
  if (bucket <= 0) {
    return 0;
  }
  var upper: i64 = 1;
  var index: i32 = 0;
  while (index < bucket) {
    upper *= 2;
    ++index;
  }
  return upper - 1;
}

fn Run() {
  Core.Print(BucketUpper(10));
}
