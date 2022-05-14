import 'binary.dart';
import 'constant.dart';
import 'expr.dart';
import 'operation.dart';

class Tokenizer {
  final String _input;
  final OperationCollection _operationCollection;

  Tokenizer(String input, OperationCollection operationCollection) 
    : _input = input, _operationCollection = operationCollection;

  Expression tokenize() {
    List<String> chars = _input.split("");
    int read = 0;
    List<ConstantExpression> numbers = [];

    while(read < chars.length) {
      String char = chars[read];

      double? number = double.tryParse(char);
      if(number != null) {
        if(numbers.length == 2) {
          throw Exception("Expected operand.");
        }

        numbers.add(ConstantExpression(number));
      } else {
        Operation? operation = _operationCollection.find(char);
              
        // if we found an operation
        if(operation != null) { 
          if(numbers.length < 1) {
            throw Exception("Expected a number.");
          }

          print("Size: ${numbers.length}");

          // Do operation
          var expr = BinaryExpression(left: numbers.first, right: numbers.last, function: operation.executor);
          double result = expr.eval();

          numbers.clear();
          numbers.add(ConstantExpression(result));

        } else {
          throw Exception("invalid operation");
        }
      }

      read++;
    }

    if(numbers.isEmpty) {
      return ConstantExpression(0);
    }

    return numbers.first;
  }
}