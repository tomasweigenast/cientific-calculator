#include <log.h>

void println(std::string text) {
    std::cout << text << std::endl;
}

void print(std::string text) {
    std::cout << text;
}

void printAll(std::initializer_list<std::string> lines) {
    for (auto line : lines)
    {
        std::cout << line << std::endl;    
    }
}

template <typename Arg, typename... Args>
void printft(Arg&& arg, Args&&... args) {
    std::cout << std::forward<Arg>(arg);
    ((std::cout << ',' << std::forward<Args>(args)), ...);
}


std::string readline() {
    std::string out;
    std::getline(std::cin, out);

    return out;
}

std::string readline(std::string text) {
    print(text);
    return readline();
}