#include <iostream>
#include <ranges>
#include <vector>
#include <fstream>

template <typename T>
void printMembership(const std::vector<T>& vector, const T& element) {
	if (std::ranges::find(vector, element) != vector.end()) {
		std::cout << "element " << element << " jest w wektorze" << std::endl;
	} else {
        std::cout << "element " << element << " nie jest w wektorze" << std::endl;
    }
	return;
}

int main() {
    // Membership
    std::cout << "------------------------------" << std::endl;
    std::cout << "Membership" << std::endl;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int el1 = 3;
    int el2 = 6;
    printMembership(vec, el1);
    printMembership(vec, el2);
    std::cout << "------------------------------" << std::endl;

    // Even squares
    std::cout << "Even squares" << std::endl;
    std::vector<int> vec2 = { 0, 1, 3, -1, 5, 10, -11, 12, 4, 7};
    auto v = vec2 | std::views::filter([](int i) { return i % 2 == 0; }) | std::views::transform([](int i) { return i * i; });

    for (const int num : v) {
	std::cout << num << std::endl;
    }

    std::cout << "------------------------------" << std::endl;

    // Response times
    std::cout << "Response times" << std::endl;
    std::ifstream in_file("dane.txt");
    std::vector<double> vec3;

    double log;
    while (in_file >> log) {
	vec3.push_back(log);
    }

	auto wynik = vec3 | std::views::drop_while([](double n) { return n != -1.0; }) | std::views::filter([](double n) { return n > 1700.1; }) | std::views::take(10) | std::views::transform([](double n) { return n * 0.001; });

    for (const auto& czas : wynik) {
	std::cout << czas << "s\n";
    }

    std::cout << "------------------------------" << std::endl;

    return 0;
}