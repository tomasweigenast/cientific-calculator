package math_parser

type MathResult interface {
	IsValid() bool
	Number() float64
}

// Represents the result of a math operation
type validMathResult struct {
	number float64
	valid  bool
}

// Creates a new valid MathResult
func NewMathResult(v float64) MathResult {
	return &validMathResult{
		number: v,
		valid:  true,
	}
}

func (m *validMathResult) IsValid() bool {
	return m.valid
}

func (m *validMathResult) Number() float64 {
	if !m.valid {
		panic("MathResult does not have a valid 'number'.")
	}

	return m.number
}
