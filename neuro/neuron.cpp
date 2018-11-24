#include "../stdafx.h"
#include "neuron.h"
// активационная функция
static float sigmoid(float x)
{
    return 1.f / (1.f + exp(-x));
}

Neuron::Neuron() : akson(Akson()), value(0.f)
{
    akson.ownerNeuron = this;
}

// посчитать результат
float Neuron::compute()
{
	if (this->dendrits.empty())
		return this->value;

	float result = 0.0f;

	for (size_t i = 0; i < this->dendrits.size(); i++) 
		result += this->dendrits[i].inputAkson->ownerNeuron->compute() * this->dendrits[i].weight;
	return this->value = sigmoid(result);
}

// функция обучения принимает ошибку и распространяет ее дальше по сети
// пока не дойдет до InputNeuron
void Neuron::study (const float error)
{
	if (this->dendrits.empty())
		return;

    const float learning_rate = 0.1f;

    float weights_delta = (this->value - error) * (this->value + 0.001f) * (1.001f - this->value);

	for (size_t i = 0; i < dendrits.size(); i++) 
		dendrits[i].weight -= dendrits[i].inputAkson->ownerNeuron->value * weights_delta * learning_rate;

    for(size_t i = 0; i < dendrits.size(); i++)
        dendrits[i].inputAkson->ownerNeuron->study(dendrits[i].weight * weights_delta);
}

// конструктор нейронов для "прокидывания" связей (дендритов) между слоями
Neuron::Neuron(std::vector<Neuron *> *prevLayout) : Neuron()
{
	for (size_t i = 0; i < prevLayout->size(); i++)
		this->dendrits.push_back(Dendrit(&prevLayout->at(i)->akson));
}
