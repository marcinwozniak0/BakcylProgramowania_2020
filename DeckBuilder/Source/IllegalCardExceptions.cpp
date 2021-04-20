#include <exception>
#include <string>

class IllegalCardException: public std::exception 
{
private:
    std::string message_;
public:
    explicit IllegalCardException(const std::string& message);
    const char* what() const noexcept override 
    {
        return message_.c_str();
    }
};


IllegalCardException::IllegalCardException(const std::string& message) : message_(message) {}