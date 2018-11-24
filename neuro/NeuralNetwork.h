#pragma once
#include "neuron.h"
class NeuralNetwork
{
private:
	std::vector<Neuron *> inLayout;
	std::vector<Neuron *> outLayout;
public:
	NeuralNetwork(size_t inputLayoutNeuronsCount, size_t outputLayoutNeuronsCount);

	NeuralNetwork();

    size_t result();

    void study(size_t expected);

    void imageSet(const unsigned int matrix[]);

	void saveWeights();

	bool loadWeights();
};
