package math_parser

import (
	"bytes"
	"strconv"
	"strings"
	"unicode"
)

type Token uint8

const (
	Token_EOL         Token = 0
	Token_Add         Token = 1
	Token_Subtract    Token = 2
	Token_Multiply    Token = 3
	Token_Divide      Token = 4
	Token_OpenParens  Token = 5
	Token_CloseParens Token = 6
	Token_Comma       Token = 7
	Token_Identifier  Token = 8
	Token_Number      Token = 9
)

type Tokenizer struct {
	currentToken      Token
	currentNumber     float64
	currentChar       rune
	currentIdentifier string
	input             *strings.Reader
}

func NewTokenizer(r *strings.Reader) *Tokenizer {
	tokenizer := &Tokenizer{
		input: r,
	}

	tokenizer.NextChar()
	tokenizer.NextToken()

	return tokenizer
}

func (t *Tokenizer) Identifier() string {
	return t.currentIdentifier
}

func (t *Tokenizer) Number() float64 {
	return t.currentNumber
}

func (t *Tokenizer) Token() Token {
	return t.currentToken
}

func (t *Tokenizer) NextChar() {
	chr, _, err := t.input.ReadRune()
	if err != nil {
		panic(err)
	}

	t.currentChar = chr
}

func (t *Tokenizer) NextToken() {
	for unicode.IsSpace(t.currentChar) {
		t.NextChar()
	}

	switch t.currentChar {
	case ';':
		t.currentToken = Token_EOL
		return

	case '+':
		t.NextChar()
		t.currentToken = Token_Add
		return

	case '-':
		t.NextChar()
		t.currentToken = Token_Subtract
		return

	case '*':
		t.NextChar()
		t.currentToken = Token_Multiply
		return

	case '/':
		t.NextChar()
		t.currentToken = Token_Divide
		return

	case '(':
		t.NextChar()
		t.currentToken = Token_OpenParens
		return

	case ')':
		t.NextChar()
		t.currentToken = Token_CloseParens
		return

	case ',':
		t.NextChar()
		t.currentToken = Token_Comma
		return
	}

	if unicode.IsDigit(t.currentChar) || t.currentChar == '.' {
		q := new(bytes.Buffer)
		haveDecimalPoint := false

		for unicode.IsDigit(t.currentChar) || (!haveDecimalPoint && t.currentChar == '.') {
			_, err := q.WriteRune(t.currentChar)
			if err != nil {
				panic(err)
			}

			haveDecimalPoint = t.currentChar == '.'
			t.NextChar()
		}

		result := q.String()

		// parse it
		var err error
		t.currentNumber, err = strconv.ParseFloat(result, 64)
		if err != nil {
			panic(err)
		}

		return
	}

	if unicode.IsLetter(t.currentChar) || t.currentChar == '_' {
		q := new(bytes.Buffer)
		for unicode.IsLetter(t.currentChar) || unicode.IsDigit(t.currentChar) || t.currentChar == '_' {
			_, err := q.WriteRune(t.currentChar)
			if err != nil {
				panic(err)
			}

			t.NextChar()
		}

		t.currentIdentifier = q.String()
		t.currentToken = Token_Identifier
		return
	}

	panic("unexpected character.")
}
