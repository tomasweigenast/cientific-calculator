import 'tokenizer.dart';

class Executor {
  final Tokenizer _tokenizer;

  Executor(Tokenizer tokenizer) : _tokenizer = tokenizer;

  double calculate() {
    return _tokenizer.tokenize().eval();
  }
}