#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
#include <string>
#include <exception>

void process(std::vector<std::string> v){};

template <class T>
void process(std::vector<std::string>& v, T&& val){
    std::stringstream ss;
    ss << val;
    v.push_back(ss.str());
}

template <class T, class... Args>
void process(std::vector<std::string>& v, T&& val, Args&&... args){
    std::stringstream ss;
    ss << val;
    v.push_back(ss.str());
    process(v, std::forward<Args>(args)...);
}

template <class... Args>
std::string format(const char* s, Args&&... args){
    std::vector<std::string> v;
    int size = sizeof...(args);
    process(v, std::forward<Args>(args)...);
    std::stringstream ss;
    for (int i = 0; s[i] != '\0'; i++){
        if (s[i] == '{'){
            size_t num = 0;
            i++;
            do{
                if (!isdigit(s[i])){
                    throw std::runtime_error("incorrect data");
                }
                num *= 10;
                num = num + s[i] - '0';
                i++;
            }
            while (s[i] != '}');
            if (num >= size){
                throw std::runtime_error("incorrect data");
            }
            else{
                ss << v[num];
            }
        }
        else if (s[i] == '}'){
            throw std::runtime_error("incorrect data");
        }
        else {
            ss << s[i];
        }
    }
    return ss.str();
}