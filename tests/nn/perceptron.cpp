#include "../../lib/nn/perceptron.hpp"

#include <iostream>

Perceptron<2>::TrainingData AndDataset()
{
    return {
        { {{ +1, +1 }}, +1 },
        { {{ +1, -1 }}, -1 },
        { {{ -1, +1 }}, -1 },
        { {{ -1, -1 }}, -1 }
    };
};

Perceptron<2>::TrainingData OrDataset()
{
    return {
        { {{ +1, +1 }}, +1 },
        { {{ +1, -1 }}, +1 },
        { {{ -1, +1 }}, +1 },
        { {{ -1, -1 }}, -1 }
    };
}

Perceptron<2>::TrainingData XorDataset()
{
    return {
        { {{ +1, +1 }}, -1 },
        { {{ +1, -1 }}, +1 },
        { {{ -1, +1 }}, +1 },
        { {{ -1, -1 }}, -1 }
    };
}

int main(void)
{
    // PERCEPTRON DATA (uses random weights)
    double LEARNING_RATE = 0.01;
    auto STEP_FUNCTION = [](auto x) { return (x > 0) ? 1 : -1; };

    Perceptron<2> operation = {
        STEP_FUNCTION,
        LEARNING_RATE
    };

    // LEARNING DATA
    Perceptron<2>::Number EPSILON = 0;
    int MAX_LEARNING = 100;
    
    Perceptron<2>::TrainingData DATA =
        AndDataset();
        // OrDataset();
        // XorDataset();

    // TRAINING CODE
    auto iterations = operation.learn(DATA, EPSILON, MAX_LEARNING);
    std::cout << "After " << iterations << " iterations learning has stopped.\n";

    // TEST
    for (const auto& datum : DATA)
    {
        auto [ input, expected ] = datum;
        auto output = operation.think(input);

        std::cout << "---\n";
        std::cout << "Input: " << input << " expects: " << expected << "\n";
        std::cout << "Got: " << output << "\n";
    }

}