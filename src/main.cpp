#include <string>
#include <app.h>
#include <test_suite.h>
#include <math_parser/operation.h>
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
		std::cout << "Welcome to the scientific calculator" << std::endl;
		Application app;
		return app.run();
	}
	
	cleanup_operations();
	AllocationMetrics::instance().print_usage();
}