export module PersonModel;
import <iostream>;
import <string>;
export class Person {
private:
	std::string name;
	int age;
public:
	Person(std::string n, int a) {
		name = n;
		age = a;
	}
	void print() {
		std::cout << name << " " << age << "\n";
	}
};