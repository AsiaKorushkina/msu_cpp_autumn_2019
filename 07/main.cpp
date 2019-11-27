#include "vector.h"

int main(int argc, char const *argv[])
{
    Vector<int> v;
    for (size_t i = 0; i < 10; i++){
        v.push_back(2 * i);
    }
    for (size_t i = 0; i < v.size(); i++){
        std::cout << v[i] << std::endl;
    }
    return 0;
}