#include <log.h>
#include <app.h>
#include <iostream>
#include <string>
#include <iomanip>

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
		// SystemEquation systemEquation(unknownsCount);
		// Node* node = new NumberNode(5);

	} catch(const std::invalid_argument&) {
	}

}

int Application::run() {
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
		} catch(const std::invalid_argument&) {
			println("Invalid option. Try again.");
		}
	}

    return 0;
}