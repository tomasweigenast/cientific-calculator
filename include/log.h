#include <iostream>
#include <initializer_list>

void println(std::string text);
void print(std::string text);
void printAll(std::initializer_list<std::string> lines);

template <typename Arg, typename... Args>
void printft(Arg&& arg, Args&&... args);

std::string readline();
std::string readline(std::string text);