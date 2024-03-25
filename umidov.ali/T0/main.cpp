#include <iostream>
#include <string>

int main() {
    char u = 'u';
    char m = 'm';
    char i = 'i';
    char d = 'd';
    char o = 'o';
    char v = 'v';
    char dot = '.';
    char a = 'a';
    char l = 'l';
    std::string name = { u, m, i, d, o, v, dot, a, l, 'i' };
    std::cout << name << '\n';
    return 0;
}
