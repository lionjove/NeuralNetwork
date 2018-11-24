#include "stdafx.h"
#include "neuro/neuron.h"
#include "neuro/NeuralNetwork.h"
#include "reading/bmp.h"

int main(int argc, char *argv[]) 
{
	std::vector<unsigned int *> images;
	std::vector<char> symbols;
	const std::string path = "alphabet\\10x10";

	// загрузка изображений и подсчет всего кол-ва изображений

	size_t filesCount = 0;
	for (auto & p : std::experimental::filesystem::v1::directory_iterator(path))
	{
		images.push_back(readBMP(p.path().string()));
		symbols.push_back(p.path().string()[path.length() + 1]);
		filesCount++;
	}

	// создание нейросети

	NeuralNetwork neuro;

	if(!neuro.loadWeights())
		neuro = NeuralNetwork(16 * 16, filesCount);

	std::cout << "started to learn" << std::endl;

	// обучение нейросети

	 bool flag = true;
	 int iteration = 0;
	while (flag) {
		iteration++;
		if (iteration % 100 == 0) 
		{
			std::cout << iteration << " epoch" << std::endl;
			neuro.saveWeights();
		}
		flag = false;
		for (size_t z = 0; z < images.size(); z++) {
			neuro.imageSet(images[z]);

			std::cout << "expected: " << symbols[z] << " found: " << symbols[neuro.result()] << std::endl;

			if(neuro.result() != z)
			{
				flag = true;
				neuro.study(z);
			}
		}
	}

	neuro.saveWeights();

	if (iteration == 1) 
		std::cout << "no learning need Neural Network ready" << std::endl;
	else 
		std::cout << "learning took " << iteration << " iterations." << std::endl;

	for (unsigned int *a : images)
		delete[] a;

	system("pause");
}
