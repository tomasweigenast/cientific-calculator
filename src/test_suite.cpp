#include <log.h>
#include <test_suite.h>
#include <iostream>
#include <programs/matrix/matrix.h>
#include <assert/assert.h>

void matrix_() 
{
	// Matrix m1 = Matrix::identity(5, 5);
	// std::cout << m1 << std::endl;

	// Matrix m2(5, 4);
	// std::cout << m2 << std::endl;

	// Matrix m3 = Matrix::zero(5, 8);
	// std::cout << m3 << std::endl;

	// Matrix m4 = Matrix::zero(3, 3);
	// std::cout << m4 << std::endl;

	// m4.set(0, 0, 2);
	// m4.set(0, 1, 17);
	// m4.set(0, 2, 6);
	// m4.set(1, 1, 8);

	// std::cout << m4 << std::endl;

	// Matrix m4diagonal = m4.main_diagonal();
	// std::cout << m4diagonal << std::endl;

	// Matrix m4secondaryDiagonal = m4.secondary_diagonal();
	// std::cout << m4secondaryDiagonal << std::endl;

	// std::cout << "Test transpose" << std::endl;
	// Matrix m5(4, 2);
	// m5.set(0, 0, 3.4);
	// m5.set(0, 1, 2);
	// m5.set(1, 0, 8);
	// m5.set(1, 1, 9);
	// m5.set(2, 0, 12);
	// m5.set(2, 1, 2.665);
	// m5.set(3, 0, 215);
	// m5.set(3, 1, 21);

	// std::cout << m5 << std::endl;
	
	// Matrix m5transpose = m5.transpose();
	// std::cout << m5transpose << std::endl;

	// Matrix m5minor = m5.complementary_minor(2, 1);
	// std::cout << m5minor << std::endl;

	std::cout << "Test determinant" << std::endl;

	Matrix m6({
		{2, 6, 1}, 
		{6, 3, 1}, 
		{2, 2, 8}
	}, 3);
	std::cout << m6 << std::endl;

	double m6Determinant = m6.determinant();
	std::cout << "Determinant: " << m6Determinant << std::endl;

	Matrix m6minor = m6.minor_complementary(3, 3);
	std::cout << m6minor << std::endl;

	// Matrix m7({{2, 6}, {6, 3}}, 2);
	// std::cout << m7 << std::endl;

	// double m7Determinant = m7.determinant();
	// std::cout << "Determinant: " << m7Determinant << std::endl;
}

void test_equality_comparison()
{
	{
		TestCase t("same size but different values");
		Matrix m1(5, 4);
		Matrix m2(2, 2);

		t.is_false(m1 == m2);

		Matrix m3(2, 2);
		Matrix m4(2, 2);
		t.is_true(m3 == m4);
	}
}

void test_matrix_emplace() 
{
	Matrix matrix(2, 2);
	matrix.emplace(2);
	matrix.emplace(5);
	matrix.emplace(9.92);
	matrix.emplace(12);

	std::cout << matrix << std::endl;
}

void TestSuite::run() {
	std::cout << "Running tests..." << std::endl;

	test_equality_comparison();
}