#include "vector.h"

void CHECK_EXPR(const bool expr){
    if (expr){
        std::cout <<"test passed"<<std::endl;
    }
    else{
        std::cout <<"test failed"<<std::endl;
    }
}

int main(int argc, char const *argv[])
{
    Vector<int> v;
    for (size_t i = 0; i < 10; i++){
        v.push_back(2 * i);
    }
    size_t size = v.size();
    v.pop_back();
    CHECK_EXPR(!v.empty());
    CHECK_EXPR(v.size() == size - 1);
    bool flag = true;
    size_t i = 0;
    for (auto it = v.rbegin(); it < v.rend(); it++){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    for (auto it = v.begin(); it < v.end(); it = it + 2){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    v.resize(size / 2);
    for (auto it = v.begin(); it < v.end(); it++){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    CHECK_EXPR(v.size() == 5);
    v.clear();
    CHECK_EXPR(v.empty());
    return 0;
}