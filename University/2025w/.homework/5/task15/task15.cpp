#include <iostream>

void stack(size_t depth = 1) { std::cout << " Call #" << depth << std::endl; stack(++depth); }

int main() { stack(); }
