#include <functional>
#include <string>
#include <app.h>
#include <iostream>

typedef std::function<DATATYPE (DATATYPE, DATATYPE)> BinaryExecutor;
typedef std::function<DATATYPE (DATATYPE)> UnaryExecutor;

static BinaryExecutor* s_AddOperation = new BinaryExecutor([](DATATYPE a, DATATYPE b) -> DATATYPE { return a+b; });
static BinaryExecutor* s_SubtractOperation = new BinaryExecutor([](DATATYPE a, DATATYPE b) -> DATATYPE { return a-b; });
static BinaryExecutor* s_MultiplyOperation = new BinaryExecutor([](DATATYPE a, DATATYPE b) -> DATATYPE { return a*b; });
static BinaryExecutor* s_DivideOperation = new BinaryExecutor([](DATATYPE a, DATATYPE b) -> DATATYPE { return a/b; });

static UnaryExecutor* s_UnaryExecutor = new UnaryExecutor([](DATATYPE a) -> DATATYPE { return -a; });

static void cleanup_operations()
{
    std::cout << "Cleaning operations..." << std::endl;
    delete s_AddOperation;
    delete s_SubtractOperation;
    delete s_MultiplyOperation;
    delete s_DivideOperation;
    delete s_UnaryExecutor;

    std::cout << "Cleaned" << std::endl;
}