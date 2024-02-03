#include "huffman.h"
#include "appSettings.h"
#include <map>
#include <queue>
#include <vector>

using namespace std;

EncodingResult* huffman::encode(char d[], int frequency[]) {
	int size = sizeof(d) / sizeof(d[0]);

	priority_queue<MinHeapNode*, vector<MinHeapNode*>, Comparator> priorityQ;

	for (int i = 0; i < size; i++) {
		auto node = new MinHeapNode(d[i],frequency[i]);
		priorityQ.push(node);
	}

	MinHeapNode* root = nullptr;

	while (priorityQ.size() > 1) {
		auto minFreqNode = priorityQ.top();
		priorityQ.pop();
		
		auto secondMinFreqNode = priorityQ.top();
		priorityQ.pop();

		auto combinedFrequency = minFreqNode->frequency + secondMinFreqNode->frequency;
		auto freq_node = new MinHeapNode('-', combinedFrequency);
		freq_node->left = minFreqNode;
		freq_node->right = secondMinFreqNode;

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
	return new EncodingResult(encodeMessage('caban'), root);
}

char* huffman::encodeMessage(char* originalMessage) {
	int index = 0;
	char* result = nullptr;
	
	for (auto character : originalMessage) {
		result += huffmanCodes[character];
		index++;
	}
	
	return result;
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

DecodingResult* huffman::decode(MinHeapNode* root, char* encodedText) {
	int textLength = sizeof(encodedText) / sizeof(encodedText[0]);
	char* result = nullptr;

	MinHeapNode* current = root;

	for (int i = 0; i < textLength; i++) {
		if (encodedText[i] == '0') {
			current = current->left;
		} else if (encodedText[i] == '1') {
			current = current->right;
		} else {
			result += current->character;
			current = root;
		}
	}
	
	return new DecodingResult(result);
}

void huffman::sort() {
	std::ifstream input(settings->inputFile);

	if (input) {
		char data;
		std::map<char, int> freq;
		while (input.get(data)) {
			freq[data]++;
		}
		input.close();

		for (const auto& wpis : freq) {
			std::cout << wpis.first << "   " << wpis.second << std::endl;
		}
	}
}

