// Design lab: model expected failures as values.
choice ParseI32Result {
  Ok(value: i32),
  Error(code: i32)
}

fn Describe(result: ParseI32Result) -> i32 {
  match (result) {
    case .Ok(value: i32) => { return value; }
    case .Error(code: i32) => { return -code; }
  }
}
