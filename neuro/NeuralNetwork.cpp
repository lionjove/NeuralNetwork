#include "../stdafx.h"
#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() 
{
}

// inputLayoutNeuronsCount -> ���������� ������� �������� � ���������
// outputLayoutNeuronsCount -> ���������� �������� �������� � ���������
NeuralNetwork::NeuralNetwork(size_t inputLayoutNeuronsCount, size_t outputLayoutNeuronsCount) : NeuralNetwork()
{
	for (size_t i = 0; i < inputLayoutNeuronsCount; i++)
		this->inLayout.push_back(new Neuron());

	for (size_t i = 0; i < outputLayoutNeuronsCount; i++)
		this->outLayout.push_back(new Neuron(&this->inLayout));
}

// ���������� ������ ��������� �������
// ������� �� ���� ��� ��������� ���� �������
size_t NeuralNetwork::result(){
	size_t idx = 0;
	float max = -1.f;

	for (size_t i = 0; i < this->outLayout.size(); i++)
	{
		if (this->outLayout[i]->compute() > max)
		{
			idx = i;
			max = this->outLayout[i]->getValue();
		}
	}

	return idx;
}

// ����� ��� �������� ��������� ��������� ������ ������� 
// ������ ���� ������� �� ���������� ��������
void NeuralNetwork::study(const size_t expected)
{
	for (size_t i = 0; i < this->outLayout.size(); i++)
		if (i == expected)
			this->outLayout[i]->study(1.0f);
		else
			this->outLayout[i]->study(0.0f);
}

// ������ ��� ������ �����������
void NeuralNetwork::imageSet(const unsigned int matrix[]){
	const float normalizeConst = 0xffffff;

	for (size_t i = 0; i < this->inLayout.size(); i++)
		this->inLayout[i]->setValue(static_cast<float>(matrix[i]) / normalizeConst);
}

// ��������� ���� ������ ����� �������
void NeuralNetwork::saveWeights () 
{
	std::ofstream out = std::ofstream("weights.txt");

	out << this->inLayout.size() << std::endl
		<< this->outLayout.size() << std::endl;

	for (size_t i = 0; i < this->outLayout.size(); i++)
	{
		for (size_t j = 0; j < this->outLayout[i]->getDendrits()->size(); j++)
			out << this->outLayout[i]->getDendrits()->at(j).weight << std::endl;
	}
}

// ��������� ���� ������ ����� �������
bool NeuralNetwork::loadWeights()
{
	std::ifstream in = std::ifstream("weights.txt");

	if (!in.is_open()) { return false; }

	std::cout << "weights loaded" << std::endl;

	size_t inLayoutSize, outLayoutSize;

	in >> inLayoutSize >> outLayoutSize;

	for(size_t i = 0; i < inLayoutSize; i++) 
		this->inLayout.push_back(new Neuron());

	for (size_t i = 0; i < outLayoutSize; i++)
		this->outLayout.push_back(new Neuron(&this->inLayout));

	for (size_t i = 0; i < outLayoutSize; i++)
		for (size_t j = 0; j < inLayoutSize; j++)
			in >> this->outLayout[i]->getDendrits()->at(j).weight;

	return true;
}