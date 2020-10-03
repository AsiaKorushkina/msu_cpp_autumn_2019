#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <sstream>
#include <algorithm>
#include <utility>
#include <cctype>
#include <vector>

bool cmp(std::pair<std::string, uint64_t>& a, std::pair<std::string, uint64_t>& b)
{
    return a.second != b.second?  a.second > b.second : a.first > b.first;
};


int main(int argc, char const *argv[])
{
    std::regex url("http://..*");
    
    std::map<std::string, uint64_t> stat;
    std::ifstream f;
    f.open("test.txt", std::ios::in);
    if (!f){
        std::cout << "Can't open file."<<std::endl;
        return 1;
    }
    std::string firstline;

    while (!f.eof()){
        std::getline(f, firstline);
        //std::cout <<"String"<< firstline<<std::endl;


        std::stringstream ss(firstline);
        std::string word;
        std::smatch m;
        
        while (std::getline(ss, word, ' ')){
            //std::cout <<word<<std::endl;
            if (regex_search(word, m, url)){
                word = word.substr(m.position());
                stat[word]++;
                std::cout<<"reg "<<word<< "|" <<std::endl;
            }

        }
    }
    std::vector<std::pair<std::string, uint64_t>> v;
    
    for (auto& i: stat){
        v.push_back(std::make_pair(i.first, i.second));
    }

    //std::sort(v.begin(), v.end(), cmp);
    int size = v.size() > 5 ? 5 : v.size();
    for (auto& i: v){
        std::cout << i.first << " " << i.second << std::endl;
        std::cout << "-----------------\n";
    }

    
    return 0;
}

