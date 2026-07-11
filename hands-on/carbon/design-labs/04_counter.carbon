// Design lab: nominal class and value semantics. This is design-first and may
// require adjustment as the nightly implementation evolves.
class Counter {
  var value: i32;

  fn Create(value: i32) -> Self {
    return {.value = value};
  }

  fn Increment(ref self) {
    ++self.value;
  }
}
