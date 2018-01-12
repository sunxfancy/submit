#include <iostream>
#include <unistd.h>

int main() {
    sleep(1);
    std::cout << "I sleep 1 second" << std::endl;
    return 0;
}