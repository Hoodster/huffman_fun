#pragma once
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "appSettings.h"

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
	char* encodedText;
	MinHeapNode *root = nullptr;

	EncodingResult(char* text, MinHeapNode* heap) {
		encodedText = text;
		root = heap;
	}
};

// struktura dla danych uzyskanych po dekodowaniu
struct DecodingResult {
	char* decodedText;

	DecodingResult(char* text) {
		decodedText = text;
	}
};

class huffman {
private:
	appSettings* settings; // ustawienia aplikacji
	std::map<char, char*> huffmanCodes; // lista klucz-wartość dla kodowań znaków
	
	char* encodeMessage(char* originalMessage);
	MinHeapNode* readFromFileRec(MinHeapNode* root, const std::ifstream& file);
	void writeToFileRec(MinHeapNode* root, const std::ofstream& file);
	void generateCharacterCodes(MinHeapNode* root, int* codesArray, int size);
public:
	// konstruktor i przypisanie ustawień aplikacji (tego co wpisał użytkownik)
	huffman(appSettings* settings) {
		this->settings = settings;
	}

	EncodingResult* encode(char d[], int frequency[]);
	DecodingResult* decode(MinHeapNode* root, char* encodedText);

	void sortInput();
	void readFromFile(MinHeapNode* root);
	void writeEncodingOutputToFile(EncodingResult* result);
	void writeDecodingOutputToFile(DecodingResult* result);
};

class Comparator {
public:
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		return r->frequency - l->frequency;
	}
};