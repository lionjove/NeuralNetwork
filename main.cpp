#include "stdafx.h"
#include "neuro/neuron.h"
#include "neuro/NeuralNetwork.h"
#include <filesystem>

std::vector<unsigned int> readBMP(std::string_view filename)
{
	std::vector<unsigned int> result;

	std::ifstream file(filename, std::ios::binary);
	if (file.is_open())
	{
		char info[54];
		file.read(info, 54);

		int size = (*reinterpret_cast<int*>(info + 18)) * (*reinterpret_cast<int*>(info + 22));
		result.resize(size, 0);

		for (size_t i = 0; i < size; i++)
			file.read(reinterpret_cast<char*>(&(result[i])), 3);
	}

	return result;
}


int main(int argc, char *argv[]) 
{
	std::vector<std::vector<unsigned int>> images;
	std::vector<char> symbols;
	const char* path = "alphabet\\10x10";

	// загрузка изображений и подсчет всего кол-ва изображений

	for (auto & p : std::filesystem::directory_iterator(path))
	{
		images.emplace_back(readBMP(p.path().string()));
		symbols.push_back(p.path().filename().c_str()[0]);
	}

	// создание нейросети

	NeuralNetwork neuro;

	if(!neuro.loadWeights())
		neuro = NeuralNetwork(16 * 16, images.size());

	std::cout << "started to learn\n";

	// обучение нейросети

	std::string expectedFoundString = "expected: S found: A\n";

	bool flag = true;
	int iteration = 0;
	while (flag)
	{
		iteration++;
		flag = false;
		for (size_t z = 0; z < images.size(); z++)
		{
			neuro.imageSet(images[z].data());

			size_t resultIdx = neuro.result();

			expectedFoundString[10] = symbols[z];
			expectedFoundString[19] = symbols[resultIdx];

			std::puts(expectedFoundString.c_str());

			if (resultIdx != z)
			{
				flag = true;
				neuro.study(z);
			}
		}
	}

	neuro.saveWeights();

	if (iteration == 1) 
		std::cout << "no learning need Neural Network ready\n";
	else 
		std::cout << "learning took " << iteration << " iterations.\n";

	//system("pause");
}
