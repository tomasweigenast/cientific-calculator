package math_parser

import (
	"errors"
	m "math"
)

type Context interface {
	ResolveConstant(name string) float64
	CallFunction(name string, arguments []float64) float64
}

type (
	defaultContext  struct{}
	variableContext struct {
		variableValue float64
		variableName  string
	}
)

var defaultContextInstance *defaultContext = &defaultContext{}

func NewContext(args ...interface{}) Context {
	if len(args) == 2 {
		variableName := args[0].(string)
		variableValue := args[1].(float64)

		return &variableContext{
			variableValue: variableValue,
			variableName:  variableName,
		}
	}

	return defaultContextInstance
}

func (*defaultContext) ResolveConstant(name string) float64 {
	f, err := defaultResolveConstant(name)
	if err != nil {
		panic(err)
	}

	return f
}

func (*defaultContext) CallFunction(name string, arguments []float64) float64 {
	return defaultCallFunction(name, arguments)
}

func (v *variableContext) ResolveConstant(name string) float64 {
	f, err := defaultResolveConstant(name)
	if err != nil {
		if name[0] == v.variableName[0] {
			return v.variableValue
		}

		panic("unknown variable " + name)
	}

	return f
}

func (*variableContext) CallFunction(name string, arguments []float64) float64 {
	return defaultCallFunction(name, arguments)
}

func defaultResolveConstant(name string) (f float64, e error) {
	if name == "pi" {
		return m.Pi, nil
	} else if name == "e" {
		return m.E, nil
	}

	return 0, errors.New("unknown constant " + name)
}

func defaultCallFunction(name string, arguments []float64) float64 {
	argumentsLen := len(arguments)
	if name == "pow" {
		if argumentsLen != 2 {
			panic("pow expects two arguments.")
		}

		return m.Pow(arguments[0], arguments[1])
	} else if name == "sqrt" {
		if argumentsLen != 2 {
			panic("sqrt expects two arguments.")
		}

		return m.Pow(arguments[0], 1/arguments[1])
	} else if name == "sin" {
		if argumentsLen != 1 {
			panic("sin expects one argument.")
		}

		return m.Sin(arguments[0])
	} else if name == "cos" {
		if argumentsLen != 1 {
			panic("cos expects one argument.")
		}

		return m.Cos(arguments[0])
	} else if name == "tan" {
		if argumentsLen != 1 {
			panic("tan expects one argument.")
		}

		return m.Tan(arguments[0])
	} else if name == "asin" {
		if argumentsLen != 1 {
			panic("asin expects one argument.")
		}

		return m.Asin(arguments[0])
	} else if name == "acos" {
		if argumentsLen != 1 {
			panic("acos expects one argument.")
		}

		return m.Acos(arguments[0])
	} else if name == "atan" {
		if argumentsLen != 1 {
			panic("atan expects one argument.")
		}

		return m.Atan(arguments[0])
	} else if name == "sum" {
		if argumentsLen != 3 {
			panic("sum expects three arguments.")
		}

		// TODO: add check to avoid decimal numbers in 'n' and 'i' variables

		// double i = arguments[0]; // desde donde empieza
		// int n = arguments[1]; // hasta donde llega la sumatoria

		// int results[n];
		// for(int i = arguments[0]; i < n; i++) {

		// }
	}

	panic("unknown function " + name)
}
