import 'expr.dart';

class ConstantExpression extends Expression {
  final double _constant;

  ConstantExpression(double value) : _constant = value;

  @override
  double eval() {
    return _constant;
  }

  @override
  String toString() => _constant.toString();
}