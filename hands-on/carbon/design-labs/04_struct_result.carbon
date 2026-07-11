// Design lab: compare named fields with positional tuple access.
fn SmallestFactor(value: i32) -> {.factor: i32, .is_prime: bool} {
  var candidate: i32 = 2;
  while (candidate < value) {
    if (value % candidate == 0) {
      return {.factor = candidate, .is_prime = false};
    }
    ++candidate;
  }
  return {.factor = value, .is_prime = true};
}
