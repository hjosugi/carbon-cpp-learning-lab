import Cpp library "<cstdio>";

fn Run() {
  let message: array(Core.Char, 6) = ('H', 'e', 'l', 'l', 'o', '!');
  for (character: Core.Char in message) {
    Cpp.putchar((character as u8) as i32);
  }
}
