#pragma once

class Neuron
{
public:
	class Akson {
	public:
		Neuron *ownerNeuron;
	};

	class Dendrit {
	public:
		Akson *inputAkson;
		float weight;
		Dendrit() : weight(0.1f)
		{
			this->inputAkson = NULL;
		}
		Dendrit(Akson *aks) : Dendrit() { this->inputAkson = aks; }
	};

	std::vector<Dendrit> dendrits;
	float value;
	Akson akson;

    Neuron();
	Neuron(std::vector<Neuron *> *prevLayout);

	void setValue(float value) { this->value = value; }
    void study (const float error);

	float getValue() { return this->value; }

	std::vector<Dendrit> *getDendrits() { return &this->dendrits; }

	float compute();
};