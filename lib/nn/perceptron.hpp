#ifndef __PERCEPTRON_HPP__
#define __PERCEPTRON_HPP__

#include <functional> // std::function 
#include <utility> // std::pair
#include <vector> // std::vector
#include <cmath> // std::abs

#include <iostream>

#include "../math/vector.hpp" // Vector, std::size_t
#include "../math/random.hpp" // getEngine

template <
    std::size_t Inputs,
    typename NumberType = double
>
struct Perceptron
{
    // TYPEDEFS

    using Number = NumberType;
    using Input = Vector<Inputs, Number>;

    using TrainingDatum = std::pair<Input, Number>;
    using TrainingData = std::vector<TrainingDatum>;

    // INTERFACES

    using Activator = std::function<Number(const Number&)>;

    // CONSTRUCTORS

    Perceptron(
        const Input& weights, 
        const Number& bias, 
        const Activator& activator,
        const Number& rate = 1
    ) :
        weights { weights },
        bias { bias },
        activator { activator },
        rate { rate },
        iterations { 0 }
    {
    }

    Perceptron(const Input& weights, const Number& bias, const Number& rate = 1) :
        Perceptron(weights, bias, [](auto x) { return x; }, rate)
    {
    }

    Perceptron(const Activator& activator, const Number& rate = 1) :
        Perceptron(Input(0), 0, activator, rate)
    {
        randomize();
    }

    Perceptron(const Number& rate = 1) :
        Perceptron([](auto x) { return x; }, rate)
    {
    }

    // ALGORITHMS

    void randomize(const Number& min = -1, const Number& max = 1)
    {
        auto engine = getEngine<Number>(min, max);

        for (auto& element : weights)
            element = engine();
        bias = engine();
    }

    Number think(const Input& input) const
    {
        // calculate the raw output, put in a step-function
        auto raw = input.dot(weights) + (1 * bias);
        return activator(raw);
    }
    Number learn(const Input& input, const Number& expected)
    {
        auto output = think(input);
        auto error = expected - output;

        // rate decides how volatile the weights are
        auto ratedError = error * rate;

        // Update all the weights
        for (int i = 0; i < input.size(); ++i)
            weights[i] += (ratedError * input[i]);
        bias += (ratedError * 1);

        iterations++;
        return error;
    }

    Number learn(const TrainingDatum& datum)
    {
        return learn(datum.first, datum.second);
    }

    std::size_t learn(const TrainingData& data, Number epsilon = 0, int stopAfter = -1)
    {
        // std::size_t startTime = iterations;
        Number average;
        int loops = 0;

        do {
            Number error = 0;

            for (const auto& datum : data)
                error += std::abs(learn(datum));
            error /= data.size();

            average = error;
            ++loops;
        } 
        while (loops < stopAfter && average > epsilon);

        return loops;
        // return iterations - startTime;
    }

    // GETTERS

    const std::size_t inputs() const
    {
        return Inputs;
    }

    const std::size_t time() const
    {
        return iterations;
    }

private:

    // DATA
    Input weights;
    Number bias;

    Activator activator;

    Number rate;

    std::size_t iterations;

};

#endif