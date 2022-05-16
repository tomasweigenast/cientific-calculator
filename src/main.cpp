#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <log.h>
#include <equation_system.h>
#include <cmath>
// #include <math_parser/node.h>
#include <math_parser/parser.h>
#include <parser_exception/unexpected_char.h>
#include <parser_exception/unknown_constant.h>

#define TEST true

void matrix_calculation_menu() {

}

void equation_system_menu() {
	try {
		// printAll({
		// 	"---- Equation system ----",
		// 	"",
		// 	"1- Calculate",
		// 	"0- Come back",
		// 	"",
		// 	"---------------------"
		// });
		std::string input = readline("How many unknowns?: ");
		int unknownsCount = std::stoi(input);

		// If 0, then exit menu
		if(unknownsCount == 0) {
			return;
		}

		// Create equation
		SystemEquation systemEquation(unknownsCount);
		Node* node = new NumberNode(5);

	} catch(std::invalid_argument) {
		println("Invalid argument. Try again.");
	}

}

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
	std::istringstream st("pi;");
	try {
		Tokenizer tokenizer(st);
		Parser parser(tokenizer);
		Context *context = new DefaultContext();

		double result = parser.parse_expression()->eval(context); 
		std::cout << "Result: " << std::setprecision(50) << result << std::endl;
	} catch(const UnexpectedCharException& ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	} catch(const UnknownConstantException& ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
}

int main(int argc, char *argv[], char* envp[])
{
	std::cout << envp << std::endl;

	println("Welcome to the scientific calculator");

	#if TEST

	run_test();

	#elif

	bool running = true;
	while(running) {
		try {
			printAll({
				"---- Option Menu ----",
				"", 
				"1- Matrix",
				"2- Equation System",
				"0- Exit",
				"",
				"--------------------"
			});
			std::string input = readline("Input your option: ");
			int option = std::stoi(input);

			switch(option) {
				case 0:
					running = false;
					println("Good bye!");
					break;
				case 1:
					matrix_calculation_menu();
					running = false;
					break;

				case 2: {
					equation_system_menu();
					running = false;
					break;
				}

				default:
					throw std::invalid_argument("invalid option");
			}
		} catch(std::invalid_argument) {
			println("Invalid option. Try again.");
		}
	}

	#endif
}
