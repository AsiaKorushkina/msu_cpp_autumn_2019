#include "BigInt.h"

void CHECK_EXPR(const bool expr, bool ans){
    if (expr != ans){
        std::cout <<"test failed"<<std::endl;
    }
    else{
        std::cout <<"test passed"<<std::endl;
    }
}

int main(int argc, char const *argv[])
{

    try{
        BigInt e("-1000l");
    }
    catch(std::string &a){
        std::cout << a <<std::endl;
    }
    BigInt a(-100);
    BigInt b("1000");
    BigInt c("9898989");
    BigInt d("0000000001");
    BigInt q("1234587485743449435345336436345346433463636636363");
    BigInt e = -a;
    CHECK_EXPR(a == b, false);
    a = b;
    CHECK_EXPR(a != b, false);
    b = std::move(c);
    CHECK_EXPR(b != c, true);
    CHECK_EXPR(d < a, true);
    CHECK_EXPR(e >= d, true);
    a = 2;
    b = 7;
    CHECK_EXPR(-b == BigInt(-7), true);
    CHECK_EXPR(a + b + 2 == BigInt(11), true);
    CHECK_EXPR(q - BigInt("234587485743449435345336436345346433463636636364") == BigInt("999999999999999999999999999999999999999999999999"), true);
    d = -100;
    CHECK_EXPR(-e - d == BigInt(0), true);
    CHECK_EXPR(-99 + d == BigInt(-199), true);
    CHECK_EXPR(q + 1 + b == BigInt("1234587485743449435345336436345346433463636636371"), true);
    CHECK_EXPR(BigInt("9999999999999999999999") + 1 == BigInt("10000000000000000000000"), true);
    return 0;
}