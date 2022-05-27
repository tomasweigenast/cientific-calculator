package math_parser

var Indeterminate MathResult = indeterminateMathResult{}

type indeterminateMathResult struct{}

func (indeterminateMathResult) IsValid() bool {
	return false
}

func (indeterminateMathResult) Number() float64 {
	panic("value is indeterminate")
}
