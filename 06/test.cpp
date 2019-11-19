#include "format.h"

void CHECK_EXPR(const bool expr){
    if (expr){
        std::cout <<"test passed"<<std::endl;
    }
    else{
        std::cout <<"test failed"<<std::endl;
    }
}

template <class... Args>
void CHECK_THROW(const char* x, Args&&... args){
    try{
        format(x, std::forward<Args>(args)...);
    }
    catch(const std::runtime_error& a){
        std::cout <<a.what()<<std::endl;
        return;
    }
    std::cout << "correct data"<<std::endl;
    return; 
}

struct Data
{
    uint64_t a;
    double b;

    friend std::ostream& operator<<(std::ostream& out, const Data& d);
};

std::ostream& operator<<(std::ostream& out, const Data& d){
    out <<"a = "<< d.a <<", b = "<<d.b;
    return out;
}

int main(int argc, char const *argv[])
{
    CHECK_EXPR(format("123 abc") == "123 abc");
    CHECK_EXPR(format("{1}+{1} = {0}", 4, "two") == "two+two = 4");
    CHECK_EXPR(format("{0} and {1}", 3.14, "test") == "3.14 and test");
    Data d = {1, -10.5};
    CHECK_EXPR(format("{0} - given structure", d) == "a = 1, b = -10.5 - given structure");
    CHECK_EXPR(format("{1}{2}{3}{0}", "aaa", 1, 2, 3) == "123aaa");
    CHECK_THROW("{1}+{1} = {0}", 4, "two");
    CHECK_THROW("{", 4);
    CHECK_THROW("");
    CHECK_THROW("{0}+3+{2}+}");    
    return 0;
}