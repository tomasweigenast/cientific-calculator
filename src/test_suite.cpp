#include <log.h>
#include <test_suite.h>
#include <iostream>
#include <programs/matrix/matrix.h>

void TestSuite::run() {
	std::cout << "Running tests..." << std::endl;

	Matrix m1 = Matrix::identity(5, 5);
	std::cout << m1 << std::endl;

	Matrix m2(5, 4);
	std::cout << m2 << std::endl;

	Matrix m3 = Matrix::zero(5, 8);
	std::cout << m3 << std::endl;

	Matrix m4 = Matrix::zero(3, 3);
	std::cout << m4 << std::endl;

	m4.set(0, 0, 2);
	m4.set(0, 1, 17);
	m4.set(0, 2, 6);
	m4.set(1, 1, 8);

	std::cout << m4 << std::endl;

	Matrix m4diagonal = m4.main_diagonal();
	std::cout << m4diagonal << std::endl;

	Matrix m4secondaryDiagonal = m4.secondary_diagonal();
	std::cout << m4secondaryDiagonal << std::endl;

	std::cout << "Test transpose" << std::endl;
	Matrix m5(4, 2);
	m5.set(0, 0, 3.4);
	m5.set(0, 1, 2);
	m5.set(1, 0, 8);
	m5.set(1, 1, 9);
	m5.set(2, 0, 12);
	m5.set(2, 1, 2.665);
	m5.set(3, 0, 215);
	m5.set(3, 1, 21);

	std::cout << m5 << std::endl;
	
	Matrix m5transpose = m5.transpose();
	std::cout << m5transpose << std::endl;
}