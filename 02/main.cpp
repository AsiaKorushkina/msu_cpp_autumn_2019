#include "LinearAllocator.h"
#include <cstring>


int main(int argc, char const *argv[])
{
	if (argc > 1){
        try{
        	LinearAllocator a(atoi(argv[1]));
        	for (int i = 2; i < argc; i++){
        		if (!strcmp(argv[i], "alloc")){
        			size_t prev_cursize = a.get_cursize();
        			char* ptr = a.alloc(atoi(argv[i + 1]));
        			if (ptr == nullptr){
        				std::cout << "Not alloc" << std::endl;
        			}
        			else {
        				std::cout << ((ptr - a.get_beg()) == prev_cursize) << std:: endl;
        			}
        		i++;
        		}
        		if (!strcmp(argv[i], "reset")){
        			a.reset();
        		}
        	}
        }
        catch(const std::bad_alloc &a){
        	std::cout <<"Bad alloc"<<std::endl;
        	return 1;
        }
	}
	else {
		std::cout << "No input" <<std::endl;
		return 1;
	}
	return 0;
}