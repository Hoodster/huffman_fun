#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "appSettings.h"
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <fstream>
#include <map>

// struktura dla node'a w drzewie
struct MinHeapNode {
	// znak
	char character;
	// częstotliwość (unsigned czyli nieujemny)
	unsigned frequency;
	// dzieci
	MinHeapNode *left, *right;

	//konstruktor
	MinHeapNode(char c, unsigned frequency) {
		character = c;
		this->frequency = frequency;
		left = right = nullptr;
	}
};

// struktura dla danych uzyskanych po kodowaniu
struct EncodingResult {
	std::string encodedText;
	MinHeapNode *root = nullptr;

	EncodingResult(std::string text, MinHeapNode* heap) {
		encodedText = text;
		root = heap;
	}
};

// struktura dla danych uzyskanych po dekodowaniu
struct DecodingResult {
	std::string decodedText;

	DecodingResult(std::string text) {
		decodedText = text;
	}
};

class huffman {
private:
	appSettings* settings; // ustawienia aplikacji
	std::map<char, char*> huffmanCodes; // lista klucz-wartość dla kodowań znaków
	
	std::vector<std::pair<char, int>> sortInput();
	std::string encodeMessage(const char* originalMessage);
	void generateCharacterCodes(MinHeapNode* root, int* codesArray, int size);

	EncodingResult* readFromFile();
	void writeEncodingOutputToFile(EncodingResult* result);
	void writeDecodingOutputToFile(DecodingResult* result);

	MinHeapNode* readFromFileRec(MinHeapNode* root, std::fstream& file);
	void writeToFileRec(MinHeapNode* root, std::fstream& file);
public:
	huffman() {}
	// konstruktor i przypisanie ustawień aplikacji (tego co wpisał użytkownik)
	huffman(appSettings* settings) {
		this->settings = settings;
	}

	EncodingResult* encode();
	DecodingResult* decode();
};

class Comparator {
public:
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		return r->frequency > l->frequency;
	}
};