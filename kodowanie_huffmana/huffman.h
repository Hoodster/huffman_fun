#pragma once
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
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

	EncodingResult(char* text, MinHeapNode* heap) {
		encodedText = text;
		root = heap;
	}
};

struct DecodingResult {
	char* decodedText;

	DecodingResult(char* text) {
		decodedText = text;
	}
};

class huffman {
private:
	appSettings* settings;
	static bool compareToRight(MinHeapNode *l, MinHeapNode *r);
	std::map<char, char*> huffmanCodes;
	char* encodeMessage(char* originalMessage);

public:
	huffman(appSettings* settings) {
		this->settings = settings;
	}

	std::vector<pair<char, int>> sortInput();
	EncodingResult* encode(char d[], int frequency[]);
	void generateCharacterCodes(MinHeapNode* root, int* codesArray, int size);
	DecodingResult* decode(MinHeapNode* root, char* encodedText);
};

class Comparator {
public:
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		return r->frequency - l->frequency;
	}
};