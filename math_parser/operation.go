package math_parser

type (
	BinaryOperation func(a, b float64) float64
	UnaryOperation  func(a float64) float64
)

var (
	AddOperation BinaryOperation = func(a, b float64) float64 {
		return a + b
	}
	SubtractOperation BinaryOperation = func(a, b float64) float64 {
		return a - b
	}
	MultiplyOperation BinaryOperation = func(a, b float64) float64 {
		return a * b
	}
	DivideOperation BinaryOperation = func(a, b float64) float64 {
		return a / b
	}
	NegativeOperation UnaryOperation = func(a float64) float64 {
		return -a
	}
)
