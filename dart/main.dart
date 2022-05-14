import 'operation.dart';
import 'tokenizer.dart';

void main() {
  String operation = "2+3";
  var operationCollection = OperationCollection.filled([
    Operation("+", (a, b) => a+b)
  ]);

  double result = Tokenizer(operation, operationCollection).tokenize().eval();

  print(result);
}