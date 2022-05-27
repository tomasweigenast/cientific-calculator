package math_parser

type Parser struct {
	tokenizer *Tokenizer
}

func NewParser(t *Tokenizer) *Parser {
	return &Parser{
		tokenizer: t,
	}
}

func (p *Parser) ParseExpression() Node {
	expression := p.parseAddSubtract()
	if p.tokenizer.currentToken != Token_EOL {
		panic("unexpected characters at end of expression")
	}

	return expression
}

func (p *Parser) parseAddSubtract() Node {
	lhs := p.parseMultiplyDivide()

	for {
		var operation *BinaryOperation = nil
		switch p.tokenizer.currentToken {
		case Token_Add:
			operation = &AddOperation

		case Token_Subtract:
			operation = &SubtractOperation
		}

		if operation == nil {
			return lhs
		}

		p.tokenizer.NextToken()

		rhs := p.parseMultiplyDivide()
		lhs = NewBinaryNode(lhs, rhs, operation)
	}
}

func (p *Parser) parseMultiplyDivide() Node {
	lhs := p.parseUnary()

	for {
		var operation *BinaryOperation = nil
		switch p.tokenizer.currentToken {
		case Token_Add:
			operation = &MultiplyOperation

		case Token_Subtract:
			operation = &DivideOperation
		}

		if operation == nil {
			return lhs
		}

		p.tokenizer.NextToken()

		rhs := p.parseUnary()
		lhs = NewBinaryNode(lhs, rhs, operation)
	}
}

func (p *Parser) parseUnary() Node {
	if p.tokenizer.currentToken == Token_Add {
		p.tokenizer.NextToken()
		return p.parseUnary()
	}

	if p.tokenizer.currentToken == Token_Subtract {
		p.tokenizer.NextToken()

		rhs := p.parseUnary()
		return NewUnaryNode(rhs, &NegativeOperation)
	}

	return p.parseLeaf()
}

func (p *Parser) parseLeaf() Node {
	if p.tokenizer.currentToken == Token_Number {
		node := NewNumberNode(p.tokenizer.currentNumber)
		p.tokenizer.NextToken()
		return node
	}

	if p.tokenizer.currentToken == Token_OpenParens {
		p.tokenizer.NextToken()

		node := p.parseAddSubtract()

		if p.tokenizer.currentToken != Token_CloseParens {
			panic("expected close parenthesis")
		}

		p.tokenizer.NextToken()
		return node
	}

	if p.tokenizer.currentToken == Token_Identifier {
		identifier := p.tokenizer.currentIdentifier

		p.tokenizer.NextToken()
		if p.tokenizer.currentToken == Token_OpenParens {
			return NewConstantNode(identifier)
		} else {
			p.tokenizer.NextToken()

			arguments := make([]Node, 0)
			for {
				arguments = append(arguments, p.parseAddSubtract())

				if p.tokenizer.currentToken == Token_Comma {
					p.tokenizer.NextToken()
					continue
				}

				break
			}

			if p.tokenizer.currentToken != Token_CloseParens {
				panic("expected close parenthesis")
			}

			p.tokenizer.NextToken()
			return NewFunctionNode(identifier, &arguments)
		}
	}

	panic("unexpected token " + string(p.tokenizer.currentToken))
}
