#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>
#include <vector>
#include <exception>

void sortData(const char* FileName, const char* outFileName, const uint64_t& N){
    auto *buf = new uint64_t[N];
    std::ifstream f1(FileName, std::ios::binary);
    if (!f1){
        delete [] buf;
        throw std::ios_base::failure(FileName + std::string(" is not opened."));
    }
    std::vector<std::string> file_name;
    int i = 0;
    while(!f1.eof()){
        f1.read(reinterpret_cast<char*>(buf), N * sizeof(uint64_t));
        auto number = f1.gcount() / sizeof(uint64_t);
        if (number){
            file_name.push_back(std::to_string(i++) + ".bin");
            file_name.push_back(std::to_string(i++) + ".bin");
        }
        std::thread t1([buf, number](){ std::sort(buf, buf + number/2);} );
        std::thread t2([buf, number](){ std::sort(buf + number/2, buf + number);});
        t1.join();
        t2.join();
        std::ofstream out1(file_name[i - 2], std::ios::binary);
        std::ofstream out2(file_name[i - 1], std::ios::binary);
        for (size_t j = 0; j < number / 2; j++){
            out1.write(reinterpret_cast<char*>(buf + j), sizeof(uint64_t));
            out2.write(reinterpret_cast<char*>(buf + number/2 + j), sizeof(uint64_t));
        }
        out1.close();
        out2.close();

    }
    f1.close();
    for (size_t i = 0; i < file_name.size()-1; i++){
        std::ifstream f1(file_name[i+1], std::ios::binary);
        if (!f1){
            delete [] buf;
            throw std::ios_base::failure(file_name[i+1] + std::string(" is not opened."));
        }
        f1.read(reinterpret_cast<char*>(buf), N * sizeof(uint64_t));
        auto k = f1.gcount() / sizeof(uint64_t);
        f1.close();
        std::ifstream m1(file_name[i], std::ios::binary);
        if (!m1){
            delete [] buf;
            throw std::ios_base::failure(file_name[i] + std::string(" is not opened."));
        }
        std::ofstream res(file_name[i+1]);
        uint64_t tmp;
        size_t pos = 0;
        m1.read(reinterpret_cast<char*>(&tmp), sizeof(uint64_t));
        while (!m1.eof()){
            if (pos >= k){
                res.write(reinterpret_cast<char*>(&tmp), sizeof(uint64_t));
                m1.read(reinterpret_cast<char*>(&tmp), sizeof(uint64_t));
                continue;
            }else{
                if (tmp < buf[pos]){
                    res.write(reinterpret_cast<char*>(&tmp), sizeof(uint64_t));
                    m1.read(reinterpret_cast<char*>(&tmp), sizeof(uint64_t));
                }else if (tmp == buf[pos]){
                    res.write(reinterpret_cast<char*>(&tmp), sizeof(uint64_t));
                    res.write(reinterpret_cast<char*>(&tmp), sizeof(uint64_t));
                    pos++;
                    m1.read(reinterpret_cast<char*>(&tmp), sizeof(uint64_t));
                }else {
                    res.write(reinterpret_cast<char*>(buf + pos), sizeof(uint64_t));
                    pos++;
                }
            }
        }
        if (pos < k){
            for (size_t i = pos; i < k; i++){
                res.write(reinterpret_cast<char*>(buf + i), sizeof(uint64_t));
            }
        }
        m1.close();
        res.close();
    }
    delete [] buf;
    for (size_t i = 0; i < file_name.size() - 1; i++){
        if (std::remove(file_name[i].c_str()) != 0){
            throw std::ios_base::failure(file_name[i] + std::string(" is not deleted."));
        }
    }
    std::rename(file_name[file_name.size() - 1].c_str(), outFileName);
    return;
}

int main() {
    try{
        uint64_t N = 1024 * 1024;
        std::cout << "Sorted test1.bin"<<std::endl;
        sortData("test1.bin", "out1.bin", N);
        std::cout << "Sorted test2.bin"<<std::endl;
        sortData("test2.bin", "out2.bin", N);
        std::cout << "Sorted test3.bin"<<std::endl;
        sortData("test3.bin", "out3.bin", N);
    }
    catch (std::ios_base::failure& a){
        std::cout << a.what() << std::endl;
    }
    return 0;
}
    