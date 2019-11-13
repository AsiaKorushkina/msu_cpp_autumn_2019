#include <iostream>
#include <cctype>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    std::ostream& out_;
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out) : out_(out){};

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:

    Error process(bool& val){
        if (val == true){
            out_ << "true" << Separator;
        }
        else {
            out_ << "false" << Separator;
        }
        return Error::NoError;
    }

    Error process(uint64_t& val){
        out_ << val << Separator;
        return Error::NoError;
    }

    template <class T>
    Error process(T&& val){
        return Error::CorruptedArchive;
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args){
        if (process(std::forward<T>(val)) == Error::NoError){
            return process(std::forward<Args>(args)...);
        }
        return Error::CorruptedArchive;
    }
};

class Deserializer
{
    std::istream& in_;
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in) : in_(in){};

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:
    Error process(bool& val){
        std::string text;
        in_ >> text;
        if (text == "true"){
            val = true;
        }
        else if (text == "false"){
            val = false;
        }
        else{
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error process(uint64_t& val){
        std::string text;
        in_ >> text;
        if (!isdigit(text[0])){
            return Error::CorruptedArchive;
        }
        val = std::stoull(text.c_str());
        return Error::NoError;
    }

    template <class T>
    Error process(T&& val){
        return Error::CorruptedArchive;
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args){
        if (process(std::forward<T>(val)) == Error::NoError){
            return process(std::forward<Args>(args)...);
        }
        return Error::CorruptedArchive;
    }

};

