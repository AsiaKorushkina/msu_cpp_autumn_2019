#include <iostream>

class LinearAllocator
{
    size_t maxsize;
    size_t cursize;
    char* beg;

public:

    LinearAllocator(size_t max_Size){
        maxsize = max_Size;
        cursize = 0;
        beg = new char[maxsize];
    };

    char* alloc(size_t size){
        if (size + cursize > maxsize){
            return nullptr;
        }
        char* p = beg + cursize;
        cursize += size;
        return p;
    }

    void reset(){
        cursize = 0;
    }

    size_t get_cursize(){
        return cursize;
    }

    char* get_beg(){
        return beg;
    }

    ~LinearAllocator(){
        maxsize = 0;
        cursize = 0;
        delete [] beg;
    }
    
};