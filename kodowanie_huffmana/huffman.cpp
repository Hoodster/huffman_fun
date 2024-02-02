#include "huffman.h"
#include "parameters.h"
#include "appSettings.h"
#include <map>

EncodingResult huffman::encode(char d[], int frequency[]) {
	int size = sizeof(d) / sizeof(d[0]);

	priority_queue<MinHeapNode*, vector<MinHeapNode*>, comparator> priorityQ;

	for (int i = 0; i < size; i++) {
		auto node = new MinHeapNode(d[i],frequency[i]);
		priorityQ.push(node);
	}

	MinHeapNode root = NULL;

	while (priorityQ.size() > 1) {
		auto minFreqNode = priorityQ.top();
		priorityQ.pop();
		
		auto secondMinFreqNode = priorityQ.poll();
		priorityQ.pop();

		auto combinedFrequency = minFreqNode.frequency + secondMinFreqNode.frequency;
		auto freq_node = new MinHeapNode('-', combinedFrequency);
		freq_node.left = minFreqNode;
		freq_node.right = secondMinFreqNode;

		root = freq_node;

		priorityQ.push(freq_node);
	}
	
	return EncodingResult('', root);
}

void huffman::generateCharacterCodes(MinHeapNode *root, int size) {
	/* najwięcej ile może mieć drzewo wyokości w najmniej
	 * optymalnym wariancie (winorośl czyli wszystkie node'y po jednej stronie)
	 * ponieważ root nie jest liczony w wysokości drzewa
	 */
	int maxTreeHeight = size - 1;
	int codesArray[maxTreeHeight];

	int top = 0;
	
	if (root->left)
	{
		codesArray[top] = 0;
		
		
	}
}

char* huffman::decode(MinHeapNode* root) {
	if (!root) {
		
	}
	return 'bajo jajo';
}

bool huffman::compareToRight(MinHeapNode* l, MinHeapNode* r) {
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

