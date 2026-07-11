// Design lab: requirements are declared by an interface.
interface Ordered {
  fn Less(self: Self, other: Self) -> bool;
}

fn Min[T: Ordered](left: T, right: T) -> T {
  if (left.Less(right)) {
    return left;
  }
  return right;
}
