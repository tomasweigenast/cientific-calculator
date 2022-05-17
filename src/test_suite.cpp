#include <log.h>
#include <test_suite.h>
#include <iostream>
#include <programs/matrix/matrix.h>

void TestSuite::run() {
	std::cout << "Running tests..." << std::endl;

	// Matrix m1 = Matrix::identity(5, 5);
	// std::cout << m1 << std::endl;

	// Matrix m2(5, 4);
	// std::cout << m2 << std::endl;

	// Matrix m3 = Matrix::zero(5, 8);
	// std::cout << m3 << std::endl;

	Matrix m4 = Matrix::zero(3, 3);
	std::cout << m4 << std::endl;

	m4.set(0, 0, 2);
	m4.set(0, 1, 17);
	m4.set(0, 2, 6);
	m4.set(1, 1, 8);

	std::cout << m4 << std::endl;

	Matrix m4diagonal = m4.main_diagonal();
	std::cout << m4diagonal << std::endl;
}