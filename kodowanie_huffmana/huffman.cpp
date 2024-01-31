#include "huffman.h"
#include "parameters.h"
#include "appSettings.h"
#include <map>

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

	//if (input) {
	//	std::string text;
	//	int freq = 0;
	//	char symbol;


	//	while (input >> text) {
	//		for (int i = 0; i < text.size(); i++) {
	//			symbol = text[i];
	//			freq++;
	//			}
	//		}

	//	std::cout << symbol << freq << std::endl;
	//	}
	//}

	if (input) {
		char data;
		std::map<char, int> freq;
		while (input) {
			data = input.get();
			freq[data]++;
		}
		input.close();

		for (const auto& wpis : freq) {
			std::cout << wpis.first << "   " << wpis.second << std::endl;
			//this->minHN.character = wpis.first;
			this->minHN.frequency = wpis.second;
		}
	}
}

