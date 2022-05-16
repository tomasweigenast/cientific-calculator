#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <log.h>
#include <app.h>
#include <test_suite.h>
#include <equation_system.h>
#include <cmath>
#include <math_parser/parser.h>
#include <parser_exception/unexpected_char.h>
#include <parser_exception/unknown_constant.h>
#include <typeinfo>


void run_test() 
{
	/*MathOperation sum("+", [](double a, double b) -> double {
		return a+b;
	});

	MathOperation subtract("-", [](double a, double b) -> double {
		return a-b;-
	});


	Node* bNode = new BinaryNode(
		new NumberNode(5),
		new NumberNode(10),
		subtract
	);

	double result = bNode->eval();

	std::cout << "Result is: " << result << std::endl;

	delete bNode;*/
	// std::string input = "10+20\0";
	std::istringstream st("pi + y;");
	try {
		Tokenizer tokenizer(st);
		Parser parser(tokenizer);
		Context *context = new VariableContext(20, "x");
		// Context *context = new DefaultContext();

		double result = parser.parse_expression()->eval(context); 
		std::cout << "Result: " << std::setprecision(50) << result << std::endl;
	} catch(const UnexpectedCharException& ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	} catch(const UnknownConstantException& ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	} catch(const UnknownVariableException& ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
}

int main(int argc, char *argv[])
{
	std::string testSuite = argv[1];

	
	// Run test suite
	if(testSuite == "test") 
	{
		TestSuite testSuite;
		testSuite.run();
	} 
	// Run calculator
	else 
	{
		println("Welcome to the scientific calculator");
		Application app;
		return app.run();
	}
}