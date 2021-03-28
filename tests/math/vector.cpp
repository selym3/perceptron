#include "../../lib/math/vector.hpp"

#include <iostream>

int main(void)
{

    Vector<3> vectorA {{ 1, 2, 3 }};
    std::cout << "Here is a vector: " << vectorA << ".\n";

    Vector<3> vectorB {{ 3, 2, 1 }};
    std::cout << "Another vector: " << vectorB << ".\n";

    std::cout << "+" << (vectorA + vectorB) << ".\n";
    std::cout << "-" << (vectorA - vectorB) << ".\n";
    std::cout << "*" << (vectorA * vectorB) << ".\n";
    std::cout << "/" << (vectorA / vectorB) << ".\n";

    std::cout << "distance" << (vectorA.distance(vectorB)) << ".\n";
    std::cout << "dot" << (vectorA.dot(vectorB)) << ".\n";
    std::cout << "length (a)" << (vectorA.length()) << ".\n";
    std::cout << "length (b)" << (vectorB.length()) << ".\n";

}