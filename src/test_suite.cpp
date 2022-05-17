#include <log.h>
#include <test_suite.h>
#include <iostream>
#include <programs/matrix/matrix.h>

void TestSuite::run() {
	std::cout << "Running tests..." << std::endl;

	Matrix m = Matrix::identity(5, 5);
	std::cout << "Identity 5x5 matrix" << std::endl;	

	std::cout << m << std::endl;
}