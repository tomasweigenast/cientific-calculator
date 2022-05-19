#pragma once

#define DATATYPE_SIZE 1

#if DATATYPE_SIZE == 0 
    #define DATATYPE double
#else
    #define DATATYPE float
#endif

struct Application {
    public:
        Application(){}
        Application(const Application&) = delete;

        int run();
};  