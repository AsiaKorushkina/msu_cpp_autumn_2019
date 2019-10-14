#include <iostream>

enum class TLexem
{
    NUM,
    ADD,
    SUB,
    MUL,
    DIV,
    END
};

TLexem nextlexem(const char* &s, int& v1){
    char c = *s++;
    while (c == ' '){
        c = *s++;
    }
    if (c >= '0' and c <='9'){
        v1 = c - '0';
        c = *s;
        while((c >= '0') and (c <='9')){
            v1 = c - '0' + 10 * v1;
            c = *(++s);
        }
        return TLexem::NUM;
    }
    switch (c){
        case '*':
            return TLexem::MUL;
        case '/':
            return TLexem::DIV;
        case '+':
            return TLexem::ADD;
        case '-':
            return TLexem::SUB;
        case '\0':
            return TLexem::END;
        default:
            throw 1;    
    }
}

int mult(const char* &s, int& v1, TLexem& curlex){
    int mul;
    switch (curlex){
        case TLexem::NUM:
            mul = v1;
            curlex = nextlexem(s, v1);
            break;
        case TLexem::SUB:
            curlex = nextlexem(s, v1);
            if (curlex != TLexem::NUM) {
                throw 1;
            }
            mul = -v1;
            curlex = nextlexem(s, v1);
            break;
        default:
            throw 1;
            break;
    }
    return mul;
}

int item(const char* &s, int& v1, TLexem& curlex){
    int exp = mult(s, v1, curlex);
    TLexem c;
    while ((curlex == TLexem::MUL) or (curlex == TLexem::DIV)){
        c = curlex;
        curlex = nextlexem(s, v1);
        int b = mult(s, v1, curlex);
        if (c == TLexem::MUL){
            exp = exp * b;
        }
        else {
            if (b == 0){
                throw -2;
            }
            exp = exp / b;
        }
    }
    return exp;
}



int expr(const char* &s, int& v1, TLexem& curlex){
    int exp = item(s, v1, curlex);
    TLexem c;
    while ((curlex == TLexem::ADD) or (curlex == TLexem::SUB)){
        c = curlex;
        curlex = nextlexem(s, v1);
        int b = item(s, v1, curlex);
        if (c == TLexem::ADD){
            exp = exp + b;
        }
        else {
            exp = exp - b;
        }
    }
    return exp;
}

int main(int argc, char *argv[])
{
    if (argc != 2){
        std::cout << "Invalid expression";
        return 1;
    }
    try{
        const char* s = argv[1];
        int v1 = 0;
        TLexem curlex = nextlexem(s, v1);
        int v = expr(s, v1, curlex);
        if (curlex == TLexem::END)
            std::cout << v;
    }
    catch(int a){
        if (a == -2){
            std::cout<<"Division by zero";
            return 1;
        }
        if (a == 1){
            std::cout<<"Invalid expression";
            return 1;
        }
        
    }  
    return 0;
}
