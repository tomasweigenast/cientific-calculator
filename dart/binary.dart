import 'expr.dart';

typedef BinaryFunction = double Function(double a, double b);

class BinaryExpression extends Expression {
  final Expression _left, _right;
  final BinaryFunction _function;
  
  BinaryExpression({required Expression left, required Expression right, required BinaryFunction function}) 
    : this._left = left, this._right = right, this._function = function;

  @override
  double eval() {
    double a = _left.eval();
    double b = _right.eval();
    return _function(a, b);
  }

}