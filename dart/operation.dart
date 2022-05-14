class Operation {
  final String _name;
  final double Function(double a, double b) _executor;

  String get name => _name;
  double Function(double a, double b) get executor => _executor;

  Operation(String name, double Function(double a, double b) executor) 
    : _name = name, _executor = executor;

  @override
  String toString() => name;
}

class OperationCollection {
  final List<Operation> _operations;

  OperationCollection() : _operations = [];
  OperationCollection.filled(List<Operation> operations) : _operations = operations; 

  void register(String operand, double Function(double a, double b) executor) {
    _operations.add(Operation(operand, executor));
  }

  Operation? find(String operand) {
    try {
      return _operations.firstWhere((element) => element._name == operand);
    } catch (_) {
      return null;
    }
  }
}