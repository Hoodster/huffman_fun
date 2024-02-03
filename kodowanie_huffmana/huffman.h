#pragma once
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "appSettings.h"

struct MinHeapNode {
	char character;
	unsigned frequency;
	MinHeapNode *left, *right;

	MinHeapNode(char c, unsigned frequency) {
		character = c;
		this->frequency = frequency;
		left = right = nullptr;
	}
};

struct EncodingResult {
	char* encodedText;
	MinHeapNode *root = nullptr;

	EncodingResult(char* text, MinHeapNode* heap)
	{
		encodedText = text;
		root = heap;
	}
};

struct decoding {
	char* decodedText;
};

class huffman {
private:
	appSettings* settings;
	std::map<char, char*> huffmanCodes;

public:
	huffman(appSettings* settings) {
		this->settings = settings;
	}
	EncodingResult encode(char d[], int frequency[]);
	void generateCharacterCodes(MinHeapNode* root, int* codesArray, int size);
	DecodingResult decode(MinHeapNode* root);
	void sort();
};

class Comparator {
public:
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		return r->frequency - l->frequency;
	}
};