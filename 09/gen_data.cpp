#include <iostream>
#include <fstream>

uint64_t getNumber(int k)
{
    return rand() % k;
}

void gen_data(std::ofstream& f, size_t expr_num, int k){
    
    uint64_t tmp;
    for (size_t i = 0; i < expr_num; i++){
        tmp = getNumber(k);
        f.write(reinterpret_cast<char*>(&tmp), sizeof(uint64_t));
    }
    f.close();
}
int main()
{
    const char* outFileName1 = "test1.bin";
    const char* outFileName2 = "test2.bin";
    const char* outFileName3 = "test3.bin";
    std::ofstream f1(outFileName1, std::ios::binary);
    std::ofstream f2(outFileName2, std::ios::binary);
    std::ofstream f3(outFileName3, std::ios::binary);
    if (f1.eof() || f2.eof() || f3.eof())
    {
        std::cerr << "Can't open" << '\n';
        return 1;
    }
    gen_data(f1, 20, 10);
    gen_data(f2, 1000000, 1000);
    gen_data(f3, 10000000, 100000);
    return 0;
}
