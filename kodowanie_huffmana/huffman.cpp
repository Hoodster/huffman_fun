#include "huffman.h"
#include "parameters.h"
#include "appSettings.h"
#include <map>
#include <queue>
#include <vector>

using namespace std;

void huffman::encode(char d[], int frequency[])
{
	int size = sizeof(d) / sizeof(d[0]);
}

bool huffman::compareToRight(MinHeapNode* l, MinHeapNode* r)
{
	return l->frequency > r->frequency;
}

void huffman::sort() {

	std::ifstream input(settings->inputFile);

	if (input) {
		char data;
		std::map<char, int> freq;
		while (input.get(data) {
			freq[data]++;
		}
		input.close();

		for (const auto& wpis : freq) {
			std::cout << wpis.first << "   " << wpis.second << std::endl
		}
	}
}

