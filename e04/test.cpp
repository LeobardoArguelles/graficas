
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

int main() {
    srand (time(NULL));
    std::cout << rand() % 3;
    return 0;
}
