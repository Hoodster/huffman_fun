#pragma once
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "appSettings.h"

struct MinHeapNode {
	char character;
	unsigned frequency;
	MinHeapNode *left, *right;

	MinHeapNode(char c, unsigned frequency)
	{
		character = c;
		this->frequency = frequency;
		left = right = NULL;
	}
};

struct encoding {

};

struct decoding {

};

class huffman {
private:
	appSettings* settings;

	static bool compareToRight(MinHeapNode *l, MinHeapNode *r);
	

public:
	huffman(appSettings* settings) {
		this->settings = settings;
	}
	void encode(char d[], int frequency[]);
	void sort();
};