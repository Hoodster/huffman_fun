#include "huffman.h"
#include "appSettings.h"

EncodingResult huffman::encode(char d[], int frequency[]) {
	int size = sizeof(d) / sizeof(d[0]);

	priority_queue<MinHeapNode*, vector<MinHeapNode*>, Comparator> priorityQ;

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
	/* najwięcej ile może mieć drzewo wyokości w najmniej
	 * optymalnym wariancie (winorośl czyli wszystkie node'y po jednej stronie)
	 * ponieważ root nie jest liczony w wysokości drzewa
	 */
	int maxTreeHeight = size - 1;
	int codes[maxTreeHeight];
	generateCharacterCodes(root, codes, 0);
	return new EncodingResult('', root);
}

void huffman::generateCharacterCodes(MinHeapNode *root, int* codesArray, int top) {
	if (root->left) {
		codesArray[top] = 0;
		generateCharacterCodes(root->left, codesArray, top + 1);
	} else if (root->right) {
		codesArray[top] = 1;
		generateCharacterCodes(root->right, codesArray, top + 1);
	} else {
		char codesCharacters[top];
		for (int i = 0; i < top; i++) {
			codesCharacters[i] = '0' + codesArray[i];;
		}
		huffmanCodes[root->character] = codesCharacters;
	}
}

char* huffman::decode(MinHeapNode* root) {
	if (!root) {
		
	}
	return 'bajo jajo';
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

