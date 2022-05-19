#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <log.h>
#include <app.h>
#include <test_suite.h>
#include <cmath>
#include <mem/alloc_metric.h> 

void* operator new(size_t size)
{
	AllocationMetrics::instance().register_alloc(size);
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	AllocationMetrics::instance().register_free(size);
	free(memory);
}

int main(int argc, char *argv[])
{
	std::string testSuite = argv[1];

	// Run test suite
	if(argc == 2 && testSuite == "test") 
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
	
	AllocationMetrics::instance().print_usage();
}