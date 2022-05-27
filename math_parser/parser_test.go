package math_parser

import (
	"math"
	"testing"
)

func TestParseExpressionEval(t *testing.T) {
	testCases := []struct {
		desc  string
		input func(c *Context) float64
		want  float64
	}{
		{
			desc: "2+5",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(2), NewNumberNode(5), &AddOperation).Eval(c)
			},
			want: 7,
		},
		{
			desc: "7-7",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(7), NewNumberNode(7), &SubtractOperation).Eval(c)
			},
			want: 0,
		},
		{
			desc: "4-128",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(4), NewNumberNode(128), &SubtractOperation).Eval(c)
			},
			want: -124,
		},
		{
			desc: "5-0",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(5), NewNumberNode(0), &SubtractOperation).Eval(c)
			},
			want: 5,
		},
		{
			desc: "0-5",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(0), NewNumberNode(5), &SubtractOperation).Eval(c)
			},
			want: -5,
		},
		{
			desc: "0-0",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(0), NewNumberNode(0), &SubtractOperation).Eval(c)
			},
			want: 0,
		},
		{
			desc: "5*1",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(5), NewNumberNode(1), &MultiplyOperation).Eval(c)
			},
			want: 5,
		},
		{
			desc: "1*5",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(1), NewNumberNode(5), &MultiplyOperation).Eval(c)
			},
			want: 5,
		},
		{
			desc: "0*5",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(0), NewNumberNode(5), &MultiplyOperation).Eval(c)
			},
			want: 0,
		},
		{
			desc: "5*0",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(5), NewNumberNode(0), &MultiplyOperation).Eval(c)
			},
			want: 0,
		},
		{
			desc: "5/1",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(5), NewNumberNode(1), &DivideOperation).Eval(c)
			},
			want: 5,
		},
		{
			desc: "1/5",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(1), NewNumberNode(5), &DivideOperation).Eval(c)
			},
			want: 0.2,
		},
		{
			desc: "5/0",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(5), NewNumberNode(0), &DivideOperation).Eval(c)
			},
			want: math.Inf(1),
		},
		{
			desc: "0/1",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(0), NewNumberNode(1), &DivideOperation).Eval(c)
			},
			want: 0,
		},
		{
			desc: "0/0",
			input: func(c *Context) float64 {
				return NewBinaryNode(NewNumberNode(0), NewNumberNode(0), &DivideOperation).Eval(c)
			},
			want: math.NaN(),
		},
	}

	for _, testCase := range testCases {
		t.Run(testCase.desc, func(t *testing.T) {
			context := NewContext()
			got := testCase.input(&context)

			if testCase.want != got {
				t.Errorf("error (want [%f] - got [%f])", testCase.want, got)
			}
		})
	}
}
