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
		left = right = NULL;
	}
};

struct EncodingResult {
	char* encodedText;
	MinHeapNode *root = NULL;

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

	static bool compareToRight(MinHeapNode *l, MinHeapNode *r);
	void sort();

public:
	huffman(appSettings* settings) {
		this->settings = settings;
	}
	EncodingResult encode(char d[], int frequency[]);
	void generateCharacterCodes(MinHeapNode* root);
	DecodingResult decode(MinHeapNode* root);
	
};