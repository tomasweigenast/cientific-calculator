package math_parser

type Node interface {
	Eval(context *Context) float64
}

type numberNode struct {
	number float64
}

type binaryNode struct {
	left, right *Node
	op          *BinaryOperation
}

type unaryNode struct {
	right *Node
	op    *UnaryOperation
}

type constantNode struct {
	constantName string
}

type functionNode struct {
	functionName string
	arguments    *[]Node
}

func NewBinaryNode(lhs, rhs Node, op *BinaryOperation) Node {
	return &binaryNode{
		left:  &lhs,
		right: &rhs,
		op:    op,
	}
}

func NewNumberNode(n float64) Node {
	return &numberNode{
		number: n,
	}
}

func NewUnaryNode(rhs Node, op *UnaryOperation) Node {
	return &unaryNode{
		right: &rhs,
		op:    op,
	}
}

func NewConstantNode(constantName string) Node {
	return &constantNode{
		constantName: constantName,
	}
}

func NewFunctionNode(functionName string, arguments *[]Node) Node {
	return &functionNode{
		functionName: functionName,
		arguments:    arguments,
	}
}

func (n *numberNode) Eval(context *Context) float64 {
	return n.number
}

func (n *binaryNode) Eval(context *Context) float64 {
	lhs := (*n.left).Eval(context)
	rhs := (*n.right).Eval(context)

	return (*n.op)(lhs, rhs)
}

func (n *unaryNode) Eval(context *Context) float64 {
	rhs := (*n.right).Eval(context)

	return (*n.op)(rhs)
}

func (n *constantNode) Eval(context *Context) float64 {
	return (*context).ResolveConstant(n.constantName)
}

func (n *functionNode) Eval(context *Context) float64 {
	args := *n.arguments
	argumentCount := len(args)
	arguments := make([]float64, argumentCount)

	for i := 0; i < argumentCount; i++ {
		arguments[i] = (args[i]).Eval(context)
	}

	return (*context).CallFunction(n.functionName, arguments)
}
