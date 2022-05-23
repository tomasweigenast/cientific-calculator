#include <functional>
#include <string>
#include <app.h>
#include <iostream>

typedef DATATYPE(*BinaryExecutor)(DATATYPE, DATATYPE);
typedef DATATYPE(*UnaryExecutor)(DATATYPE);

static const BinaryExecutor& add_operation()
{
    static BinaryExecutor operation = [](DATATYPE a, DATATYPE b) -> DATATYPE { return a + b; };
    return operation;
}

static const BinaryExecutor& subtract_operation()
{
    static BinaryExecutor operation = [](DATATYPE a, DATATYPE b) -> DATATYPE { return a - b; };
    return operation;
}

static const BinaryExecutor& multiply_operation()
{
    static BinaryExecutor operation = [](DATATYPE a, DATATYPE b) -> DATATYPE { return a * b; };
    return operation;
}

static const BinaryExecutor& divide_operation()
{
    static BinaryExecutor operation = [](DATATYPE a, DATATYPE b) -> DATATYPE { return a / b; };
    return operation;
}

static const UnaryExecutor& unary_operation()
{
    static UnaryExecutor operation = [](DATATYPE a) -> DATATYPE { return -a; };
    return operation;
}