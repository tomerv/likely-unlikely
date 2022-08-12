#include <string_view>
#include <string>

void validate(std::string_view sv)
{
    if (sv.size() < 8) {
        throw std::string("password too short");
    }
}

