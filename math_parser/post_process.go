package math_parser

// Function executed after a leaf node is evaluated
type MathPostProcessor func(i float64, c Context) (f MathResult, err error)

var NotANumberProcessor MathPostProcessor = notANumberProcessor

func notANumberProcessor(i float64, c Context) (f MathResult, err error) {
	if i != i {
		return Indeterminate, nil
	}

	return NewMathResult(i), nil
}
