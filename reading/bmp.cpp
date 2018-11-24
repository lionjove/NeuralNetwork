#include "../stdafx.h"
#include "bmp.h"

unsigned int* readBMP(std::string filename)
{
	std::ifstream file = std::ifstream(filename, std::ios::binary);

	if (!file.is_open())
		return NULL;

	char info[54];
	file.read(info, 54);

	int size = *reinterpret_cast<int *>(info + 18) * *reinterpret_cast<int *>(info + 22);

	register unsigned int *result = new unsigned int[size];
	memset(result, 0, sizeof(unsigned int) * size);

	for (size_t i = 0; i < size; i++)
		file.read(reinterpret_cast<char *>(result + i), 3);

	return result;
}
