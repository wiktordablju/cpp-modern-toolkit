#include <iostream>
#include <regex>
#include <string>

bool matchesEmailFormat(const std::string& str) {
    std::regex reg1("^[a-z]{2}[0-9]{6}@example.org$");
    if (std::regex_match(str, reg1)) {
    return true;}
    else {
    return false;}
}

std::string convertDate(const std::string& str) {
    std::regex reg2("(\\d{2})/(\\d{2})/(\\d{4})");
    std::string res = std::regex_replace(str, reg2, "$2.$1.$3");
    return res;
}

int countMixedCaseMatches(const std::string& str) {
    std::regex reg3("([a-z][A-Z]|[A-Z][a-z])+");
    std::smatch matches;
    std::string::const_iterator str_iter = str.cbegin();
    int times = 0;
    while (regex_search(str_iter, str.cend(), matches, reg3)){
        ++times;
        str_iter = matches[0].second;
    }
    return times;
}

int main()
{
// Email format
std::cout << "Email format" << std::endl;
std::string str1 = "ab123456@example.org";
std::string str2 = "aaa122@example.org";
std::cout << str1 << ": " << matchesEmailFormat(str1) << std::endl;
std::cout << str2 << ": " << matchesEmailFormat(str2) << std::endl;
std::cout << "---------------" << std::endl;

// Date conversion
std::cout << "Date conversion" << std::endl;
std::string str3 = "03/16/2026";
std::cout << "w formacie amerykanskim: " << str3 << std::endl;
std::cout << "po przekonwertowaniu: " << convertDate(str3) << std::endl;
std::cout << "---------------" << std::endl;

// Mixed-case matches
std::cout << "Mixed-case matches" << std::endl;
std::string str4 = "AbCd bCdA aaaa ASDF  ";
std::cout << "liczba wystapien: " << countMixedCaseMatches(str4) << std::endl;
std::cout << "---------------" << std::endl;

}