#include <iostream>
#include <fstream>

size_t lenFile(std::ifstream& f){
    f.seekg(0, f.end);
	size_t size = f.tellg() / sizeof(uint64_t);
	f.seekg(0, f.beg);
	return size;
}

bool CHECK(std::ifstream& f, size_t size){
    size_t sizeout = lenFile(f);
	if (size != sizeout){
		return true;
	}
	uint64_t prev, next;
	f.read(reinterpret_cast<char*>(&prev), sizeof(uint64_t));
	while (!f.eof()){
		f.read(reinterpret_cast<char*>(&next), sizeof(uint64_t));
		if (prev <= next){
			prev = next;
		}else{
			return true;
		}   
	}
	return false;
}

int main(int argc, char const *argv[])
{
	std::ifstream f1("test1.bin", std::ios::binary);
	std::ifstream f2("test2.bin", std::ios::binary);
	std::ifstream f3("test3.bin", std::ios::binary);
	
	size_t l1 = lenFile(f1);
	size_t l2 = lenFile(f2);
	size_t l3 = lenFile(f3);

	f1.close();
	f2.close();
	f3.close();

	std::ifstream out1("out1.bin", std::ios::binary);
	std::ifstream out2("out2.bin", std::ios::binary);
	std::ifstream out3("out3.bin", std::ios::binary);
	bool err1 = CHECK(out1, l1);
	if (err1){
		std::cout << "Test failed" << std::endl;
	}else{
		std::cout << "Test passed" << std::endl;
	}
	out1.close();
	bool err2 = CHECK(out2, l2);
	if (err2){
		std::cout << "Test failed" << std::endl;
	}else{
		std::cout << "Test passed" << std::endl;
	}
	out2.close();
	bool err3 = CHECK(out3, l3);
	if (err3){
		std::cout << "Test failed" << std::endl;
	}else{
		std::cout << "Test passed" << std::endl;
	}
	out3.close();
	return 0;
}