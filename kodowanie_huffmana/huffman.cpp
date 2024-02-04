#include "huffman.h"
#include "appSettings.h"
#include <map>
#include <queue>
#include <vector>

using namespace std;

/*
 * główna funkcja dla kodowania huffmana, na końcu zapisuje plik o wskazanej nazwie z zakodowanym tekstem oraz drzewem
 */
EncodingResult* huffman::encode(char d[], int frequency[]) {
	int size = sizeof(d) / sizeof(d[0]); // ilość elementów

	priority_queue<MinHeapNode*, vector<MinHeapNode*>, Comparator> priorityQ; // kolejka z priorytetem na namniejszą częstotliwość wystąpień

	//wrzucenie wszystkiego do kolejki
	for (int i = 0; i < size; i++) {
		auto node = new MinHeapNode(d[i],frequency[i]);
		priorityQ.push(node);
	}

	MinHeapNode* root = nullptr; // korzeń drzewa

	while (priorityQ.size() > 1) {
		auto minFreqNode = priorityQ.top();
		priorityQ.pop();
		
		auto secondMinFreqNode = priorityQ.top();
		priorityQ.pop();
		// pobieramy dwa pierwsze node'y i usuwamy z kolejki

		auto combinedFrequency = minFreqNode->frequency + secondMinFreqNode->frequency; // dodajemy do siebie ich częstotliwości
		auto freq_node = new MinHeapNode('-', combinedFrequency); // tworzymy roboczy node, ponieważ interesują nas częstotliwości, placeholderem będzie '-'
		freq_node->left = minFreqNode; // przypisujemy jako lewą i prawą gałąź pobrane node'y
		freq_node->right = secondMinFreqNode;

		root = freq_node; // nadpisujemy root by zbudować drzewo potrzebne do późniejszych kodowań

		priorityQ.push(freq_node); // nowy node wrzucamy do kolejki
	}
	/* najwięcej ile może mieć drzewo wyokości w najmniej
	 * optymalnym wariancie (winorośl czyli wszystkie node'y po jednej stronie)
	 * ponieważ root nie jest liczony w wysokości drzewa
	 */
	int maxTreeHeight = size - 1;
	int codes[maxTreeHeight]; // możliwa długość kodu dla znaku
	generateCharacterCodes(root, codes, 0); // generowanie kodów huffmana dla znaków
	return new EncodingResult(encodeMessage('caban'), root); // zwracamy wyniki generując skompresowaną wiadomość w locie
}

// kodowanie wiadomości z tablicy kodów
char* huffman::encodeMessage(char* originalMessage) {
	char* result = nullptr;
	
	// dla każdego znaku znajdź jego wartość i dodaj do wiadomości.
	// Znak służy jako klucz:
	//		f: 01001,
	//		a: 01
	for (auto character : originalMessage) { 
		result += huffmanCodes[character];
	}
	
	return result;
}

//pobranie node'a z wiersza i przejście dalej do gałęzi potomnych, algorytm to deep first search (DFS)
//powiedz kokotowi to się zesra
MinHeapNode* huffman::readFromFileRec(MinHeapNode* root, const std::ifstream& file) {
	char* value;
	
	// exit condition
	if (!(file >> value)) {
		return nullptr;
	}

	auto* node = new MinHeapNode(value[0], value[2]);
	node->left = readFromFileRec(root->left, file);
	node->right = readFromFileRec(root->right, file);
}

// to co wyżej tylko zapisywanie wierszy
void huffman::writeToFileRec(MinHeapNode* root, const std::ofstream& file) {
	if (root == nullptr) {
		return;
	}

	file << root->character << " " << root->frequency << std::endl;

	writeToFileRec(root->left, file);
	writeToFileRec(root->right, file);
}

/*
 * stworzenie tablicy kodów mówiącej tyle, że
 * od root musisz posuwać się w lewo jeżeli 0 i prawo jeżeli 1 czyli
 * jeżeli mamy 110100 to będzie RRLRLL dla litery.
 * Często pojawiające się znaki będą miały najkrótsze drogi typu f: 0
 */
void huffman::generateCharacterCodes(MinHeapNode *root, int* codesArray, int top) {
	if (root->left) {
		codesArray[top] = 0;
		generateCharacterCodes(root->left, codesArray, top + 1); //rekurencja, przechodzimy do następnej pozycji kodu dla literki i powtarzamy porównania 
	} else if (root->right) {
		codesArray[top] = 1;
		generateCharacterCodes(root->right, codesArray, top + 1);
	} else {
		char codesCharacters[top];
		for (int i = 0; i < top; i++) {
			codesCharacters[i] = '0' + codesArray[i]; //zmiana int na char poprzez dodanie znakowego 0. Śmieszny trick ogólnie w cpp.
		}
		huffmanCodes[root->character] = codesCharacters; //przypisanie kodu do znaku
	}
}

// główna funkcja do dekodowania
DecodingResult* huffman::decode(MinHeapNode* root, char* encodedText) {
	int textLength = sizeof(encodedText) / sizeof(encodedText[0]);
	char* result = nullptr;

	MinHeapNode* current = root;

	// odwrócenie tablicy kodów z generateCharacterCodes()
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
