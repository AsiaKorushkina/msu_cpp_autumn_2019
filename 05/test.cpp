#include "Serializer.h"
#include <sstream>

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;
    bool d;
    bool e;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d, e);
    }
};

struct FalseData
{
    int a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b);
    }
};

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
    Data x { 1, true, 2, false, true};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0, false, false};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    CHECK_EXPR(err == Error::NoError, 1);
    CHECK_EXPR(x.a == y.a, 1);
    CHECK_EXPR(x.b == y.b, 1);
    CHECK_EXPR(x.c == y.c, 1);
    CHECK_EXPR(x.d == y.d, 1);
    CHECK_EXPR(x.e == y.e, 1);
    
    FalseData a = {-10, true};
    
    const Error err2 = serializer.save(a);
    CHECK_EXPR(err2 == Error::CorruptedArchive, 1);
    return 0;
}