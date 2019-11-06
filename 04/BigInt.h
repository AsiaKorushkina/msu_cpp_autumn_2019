#include <iostream>
#include <cstring>

const size_t BUF = 1;
const int Base = 10;

class BigInt
{
	bool isNeg;
	char* data;
	size_t len_data;

public:
	BigInt(): isNeg(false), data(nullptr), len_data(0){};

	BigInt(int x): isNeg(x < 0){
		std::string cur = std::to_string(!isNeg ? x : -x);
		len_data = cur.length();
		data = new char [len_data];
		for (size_t i = 0; i < len_data; i++){
			data[i] = cur[len_data - i - 1];
		}
	};
    
    BigInt(const std::string& s): isNeg(s[0] == '-'? true : false), len_data(isNeg? s.length() - 1:s.length()){
    	std::string cur = isNeg ? s.substr(1, len_data) : s;
    	int count = 0;
    	while ((cur[count] == '0') and (cur.length() - count > 1)){
    		len_data -= 1;
    		count++;
    	}
    	if (count){
    		cur = cur.substr(count, len_data);
    	}
    	data = new char [len_data];
    	for (size_t i = 0; i < len_data; i++){
    		if ((cur[len_data - i - 1] >= '0') and (cur[len_data - i - 1] <= '9')){
    			data[i] = cur[len_data - i - 1];
    		}
    		else{
    			delete [] data;
    			throw std::string("String contains incorrect characters");
    		}
			
		}
    }

    BigInt(const BigInt& x):isNeg(x.isNeg), len_data(x.len_data){
    	data = new char [len_data];
    	std::memcpy(data, x.data, len_data);
    }

    BigInt& operator=(const BigInt& x){
    	if (this == &x){
    		return *this;
    	}
    	isNeg = x.isNeg;
    	len_data = x.len_data;
    	char* ptr = new char [len_data];
    	delete [] data;
    	data = ptr;
    	std::copy(x.data, x.data + len_data, data);
    	return *this;
    }

    BigInt(BigInt&& moved): isNeg(moved.isNeg), data(moved.data), len_data(moved.len_data){
    	moved.isNeg = false;
    	moved.data = nullptr;
    	moved.len_data = 0;
    };

    BigInt& operator=(BigInt&& moved){
    	if (this == &moved){
    		return *this;
    	}
    	delete [] data;
    	isNeg = moved.isNeg;
    	len_data = moved.len_data;
    	data = moved.data;
    	moved.data = nullptr;
    	moved.isNeg = false;
    	moved.len_data = 0;
    	return *this;
    }

	~BigInt(){
		delete[] data;
	};


	BigInt operator-() const{
		BigInt tmp = *this;
		tmp.isNeg = ! (this -> isNeg);
		return tmp;
	}

	bool operator==(const BigInt& x) const{
		if ((isNeg == x.isNeg) and (len_data == x.len_data)){
            for (size_t i = 0; i < len_data; i++){
            	if (data[i] != x.data[i]){
            		return false;
            	}
            }
            return true;
		}
		else {
			return false;
		}
	}

	bool operator!=(const BigInt& x) const{
		return !(*this == x);
	}

    bool operator<(const BigInt& x) const{
    	if (isNeg == x.isNeg){
    		if (len_data != x.len_data){
    			if (isNeg){
    				return len_data > x.len_data;
    			}
    			else{
    				return len_data < x.len_data;
    			}
    		}
    		else{
    			for (size_t i = 0; i < len_data; i++){
    				if (data[len_data - i - 1] < x.data[len_data - i - 1]){
    					return true;
    				}
    			}
    			return false;
    		}
    	}
    	return isNeg;
    }

    bool operator<=(const BigInt& x) const{
    	return (*this < x) or (*this == x);
    }

    bool operator>(const BigInt& x) const{
    	return !(*this < x) and (*this != x);
    }

    bool operator>=(const BigInt& x) const{
    	return !(*this < x);
    }

    friend BigInt operator+(const BigInt& left, const BigInt& right);
    friend BigInt operator-(const BigInt& left, const BigInt& right);
	friend std::ostream& operator<<(std::ostream& out, const BigInt& x);
};

std::ostream& operator<<(std::ostream &out, const BigInt& x)
{
	if (x.isNeg == true){
    	out << '-';
    }
    for (size_t i = 0; i < x.len_data; i++){
    	out << x.data[x.len_data - i - 1];
    }
    out << std::endl;
    return out;
}

BigInt operator+(const BigInt& left, const BigInt& right){
	{
        if (left.isNeg){
        	if (right.isNeg){
        		return -(-left + -right);
        	}
        	else {
        		return right - (-left);
        	}
        }
        else{
        	if (right.isNeg){
        		return left - (-right);
        	}
        	else{		
        		BigInt tmp;
        		int len_d = std::max(left.len_data, right.len_data) + BUF; 
        		int* res = new int [len_d];
        		tmp.len_data = len_d;
        		for (size_t i = 0; i < len_d; i++){
        			res[i] = 0;
        		}
        		for (size_t i = 0; i < len_d - 1; i++)
        		{
        			res[i] += ((i < left.len_data)? left.data[i] - '0' : 0 ) + ((i < right.len_data)? right.data[i] - '0' : 0);
        			res[i + 1] = res[i] / Base;
        			res[i] = res[i] % Base;
        		}
                if (res[len_d - 1] == 0){
                	tmp.len_data = len_d - 1;
                }
                tmp.data = new char [len_d];
                for (size_t i = 0; i < tmp.len_data; i++){
                	tmp.data[i] = res[i] + '0';
                }
                delete [] res;
                return tmp;
        	}
        }
    }
}

BigInt operator-(const BigInt& left, const BigInt& right){
	if (right.isNeg){
		return left + (-right);
	}
	else {
	    if (left.isNeg){
	    	return -(-left + right);
	    }
	    else {
	    	if (left < right){
	    		return -(right - left);
	    	}
            BigInt tmp = left;
    		int len_d = left.len_data;
    		int count = 0;
    		int* res = new int [len_d];
    		for (size_t i = 0; i < len_d; i++){
    			res[i] = left.data[i] - '0';
    		}


    		for (size_t i = 0; i < len_d - 1; ++i)
    		{
    		    res[i] -= (i < right.len_data)? (right.data[i] - '0') : 0;
    		    res[i + 1] -=(res[i] < 0);
                if (res[i] < 0){
                	res[i] += Base;
                }
    		}
    		res[len_d - 1] -= (len_d - 1 < right.len_data)? (right.data[len_d - 1] - '0') : 0;
    		while ((res[len_d - 1 - count] == 0) and (len_d - count > 1)){
    		    tmp.len_data -= 1;
    		    count++;
    	    }
    	    for (size_t i = 0; i < tmp.len_data; i++){
                tmp.data[i] = res[i] + '0';
    	    }
    	    delete [] res;
    		return tmp;
	    }
	}
}