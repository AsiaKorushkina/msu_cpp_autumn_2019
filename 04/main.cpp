#include "BigInt.h"

int main(int argc, char const *argv[])
{
    BigInt a = 2;
    BigInt b = 7;
    BigInt c = b + a + 2;
    std::cout <<c;
    return 0;
}