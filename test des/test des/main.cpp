#include <iostream>
#include <vector>
struct X {
    static int i;
    X() {--i; std::cout << i << '\t';}
    ~X() {std::cout << i << '\t'; ++i;}
};
int X :: i = 5;
int main () {
    std::vector<X> x (3);
    std::cout << std::endl << "..." << std::endl;
    return 0;
}
