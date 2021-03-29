#include "../../lib/nn/perceptron.hpp"

#include <iostream>

auto STEP_FUNCTION = [](auto x) { return (x > 0) ? 1 : -1; };

/*
Create a trained perceptron given some data
and an accepted error
*/
template <std::size_t Inputs>
Perceptron<Inputs> TrainedPerceptron(
    const typename Perceptron<Inputs>::TrainingData& data, 
    double epsilon = 0, 
    int maxIterations = 100
) {
    Perceptron<Inputs> perceptron = {
        typename Perceptron<Inputs>::Input(0),
        0,
        STEP_FUNCTION
    };

    perceptron.learn(data, epsilon, maxIterations);

    return perceptron;
}

Perceptron<2> OrPerceptron(Perceptron<2>::Number epsilon = 0, int maxIterations = 100)
{
    Perceptron<2>::TrainingData data = {
        { {{ +1, +1 }}, +1 },
        { {{ +1, -1 }}, +1 },
        { {{ -1, +1 }}, +1 },
        { {{ -1, -1 }}, -1 }
    };

    return TrainedPerceptron<2>(data, epsilon, maxIterations);
}

Perceptron<2> AndPerceptron(Perceptron<2>::Number epsilon = 0, int maxIterations = 100)
{
    Perceptron<2>::TrainingData data = {
        { {{ +1, +1 }}, +1 },
        { {{ +1, -1 }}, -1 },
        { {{ -1, +1 }}, -1 },
        { {{ -1, -1 }}, -1 }
    };

    return TrainedPerceptron<2>(data, epsilon, maxIterations);
}

Perceptron<1> NotPerceptron(Perceptron<1>::Number epsilon = 0, int maxIterations = 100)
{
    Perceptron<1>::TrainingData data = {
        { {{ +1 }}, -1 },
        { {{ -1 }}, +1 }
    };

    return TrainedPerceptron<1>(data, epsilon, maxIterations);
}

struct XOR_Gate
{

    Perceptron<2> orGate;
    Perceptron<2> andGate;
    Perceptron<1> notGate;

    XOR_Gate() :
        orGate  { OrPerceptron()  },
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