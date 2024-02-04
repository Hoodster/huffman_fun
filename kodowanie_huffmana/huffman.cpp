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

MinHeapNode* huffman::readFromFileRec(MinHeapNode* root, const std::ifstream& file) {
	char* value;
	if (!(file >> value)) {
		return nullptr;
	}

	auto* node = new MinHeapNode(value[0], value[2]);
	node->left = readFromFileRec(root->left, file);
	node->right = readFromFileRec(root->right, file);
}

void huffman::writeToFileRec(MinHeapNode* root, const std::ofstream& file) {
	if (root == nullptr) {
		return;
	}

	file << root->character << " " << root->frequency << std::endl;

	writeToFileRec(root->left, file);
	writeToFileRec(root->right, file);
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

bool compareSort(pair<char, int>& a, pair<char, int>& b) {
	return a.second < b.second;
}

std::vector<pair<char, int>> huffman::sortInput() {

	std::ifstream input(settings->inputFile);

	if (input) {
		char data;
		char character;
		char frequency;
		std:vector<pair<char, int>> vec;
		std::map<char, int> freq;
		while (input.get(data)) {
			freq[data]++;
		}
		input.close();

		for (const auto& char_freq : freq) {
			vec.push_back(char_freq);
		}

		sort(vec.begin(), vec.end(), compareSort);

		return vec;
		}
}

void huffman::readFromFile(MinHeapNode* root) {
	std::ifstream file(settings->inputFile);

	root = readFromFileRec(root, file);
	file.close();
}

void huffman::writeEncodingOutputToFile(EncodingResult* result) {
	std::ofstream file(settings->outputFile);
	if (!file.is_open()) {
		std::cerr << "Error while opening file" << std::endl;
		return;
	}
	file << result->encodedText << std::endl;
	writeToFileRec(result->root, file);
	
	file.close();
}

void huffman::writeDecodingOutputToFile(DecodingResult* result) {
	std::ofstream file(settings->outputFile);
	if (!file.is_open()) {
		std::cerr << "Error while opening file" << std::endl;
		return;
	}

	file << result->decodedText << std::endl;
	file.close();
}
