#include "../../lib/nn/perceptron.hpp"

#include <iostream>

auto STEP_FUNCTION = [](auto x) { return (x > 0) ? 1 : -1; };

Perceptron<2> OrPerceptron(Perceptron<2>::Number epsilon = 0, int maxIterations = 100)
{
    Perceptron<2>::TrainingData data = {
        { {{ +1, +1 }}, +1 },
        { {{ +1, -1 }}, +1 },
        { {{ -1, +1 }}, +1 },
        { {{ -1, -1 }}, -1 }
    };

    Perceptron<2> orPerceptron = {
        Perceptron<2>::Input(0), 
        0,
        STEP_FUNCTION
    };

    orPerceptron.learn(data, epsilon, maxIterations);

    return orPerceptron;
}

Perceptron<2> AndPerceptron(Perceptron<2>::Number epsilon = 0, int maxIterations = 100)
{
    Perceptron<2>::TrainingData data = {
        { {{ +1, +1 }}, +1 },
        { {{ +1, -1 }}, -1 },
        { {{ -1, +1 }}, -1 },
        { {{ -1, -1 }}, -1 }
    };

    Perceptron<2> andPerceptron = {
        Perceptron<2>::Input(0), 
        0,
        STEP_FUNCTION
    };

    andPerceptron.learn(data, epsilon, maxIterations);

    return andPerceptron;
}

Perceptron<1> NotPerceptron(Perceptron<1>::Number epsilon = 0, int maxIterations = 100)
{
    Perceptron<1>::TrainingData data = {
        { {{ +1 }}, -1 },
        { {{ -1 }}, +1 }
    };

    Perceptron<1> notPerceptron = {
        Perceptron<1>::Input(0), 
        0,
        STEP_FUNCTION
    };

    notPerceptron.learn(data, epsilon, maxIterations);

    return notPerceptron;
}

struct XOR_Gate
{

    Perceptron<2> orGate;
    Perceptron<2> andGate;
    Perceptron<1> notGate;

    XOR_Gate() :
        orGate { OrPerceptron() },
        andGate { AndPerceptron() },
        notGate { NotPerceptron() }
    {
    }

    double think(const Vector<2>& inputs)
    {   
        // first layer
        double andResult = andGate.think(inputs);
        double orResult = orGate.think(inputs);

        // second layer
        double notResult = notGate.think(Vector<1>(andResult));
        
        // final layer (reuses andGate)
        double output = andGate.think(Vector<2>({ notResult, orResult }));

        return output;
    }
};

int main(void)
{
    XOR_Gate xorGate;

    Perceptron<2>::TrainingData data = {
        { {{ +1, +1 }}, -1 },
        { {{ +1, -1 }}, +1 },
        { {{ -1, +1 }}, +1 },
        { {{ -1, -1 }}, -1 }
    };

    std::cout << "Testing XOR: \n\n";

    for (const auto& datum : data) {
        auto [ input, expected ] = datum;
        auto output = xorGate.think(input);

        std::cout << "---\n";
        std::cout << "Input " << input << " expects " << expected << "\n";
        std::cout << "Got: " << output << "\n";
    }

}