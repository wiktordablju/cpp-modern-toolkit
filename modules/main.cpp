import Addition;
import Arithmetic;
import Parity;
import Powers;
import Factorials;
import Maximum;
import ArraySum;
import PersonModel;
import StudentModel;
import AnimalSounds;
#include <iostream>

int main()
{
    // Addition
    std::cout << "Addition" << std::endl;
    std::cout << "3+2=" << add(3, 2) << std::endl;
    std::cout << "----------" << std::endl;

    // Arithmetic
    std::cout << "Arithmetic" << std::endl;
    std::cout << "1+6=" << add(1, 6) << std::endl;
    std::cout << "10-7=" << substract(10, 7) << std::endl;
    std::cout << "3*7=" << multiply(3, 7) << std::endl;
    std::cout << "----------" << std::endl;

    // Parity
    std::cout << "Parity" << std::endl;
    std::cout << "czy liczba dwa jest parzysta " << isEven(2) << std::endl;
    std::cout << "czy liczba trzy jest parzysta " << isEven(3) << std::endl;
    std::cout << "----------" << std::endl;

    // Powers
    std::cout << "Powers" << std::endl;
    std::cout << "3 do potegi trzeciej: " << power(3, 3) << std::endl;
    std::cout << "----------" << std::endl;

    // Factorials
    std::cout << "Factorials" << std::endl;
    std::cout << "4!= " << factorial(4) << std::endl;
    std::cout << "----------" << std::endl;

    // Maximum
    std::cout << "Maximum" << std::endl;
    std::cout << "najwieksza liczba ze zbioru {3,7,1} jest: " << max(3, 7, 1) << std::endl;
    std::cout << "----------" << std::endl;

    // ArraySum
    std::cout << "ArraySum" << std::endl;
    int array[] = { 2, 1, 3, 7 };
    std::cout << "suma listy [2,1,3,7] jest: " << sumArray(array, 4) << std::endl;
    std::cout << "----------" << std::endl;

    // PersonModel
    std::cout << "PersonModel" << std::endl;
    Person pers("Wiktor", 21);
    //std::cout << "Dane osoby: " << pers.print() << std::endl;
    std::cout << "Dane osoby: ";
    pers.print();
    std::cout << "----------" << std::endl;

    // StudentModel
    std::cout << "StudentModel" << std::endl;
	Student w("Wiktor");
	w.setGrade(5);
	std::cout << "Ocena: " << w.getGrade() << std::endl; 
    std::cout << "----------" << std::endl;

    // AnimalSounds
    std::cout << "AnimalSounds" << std::endl;
    dogSound();
    catSound();
    elephantSound();
    std::cout << "----------" << std::endl;


}