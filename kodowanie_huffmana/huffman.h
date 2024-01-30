#pragma once
#include <map>
#include "appSettings.h"

struct minHeapNode { //najmniejsza liczba
	char character;
	unsigned frequency;
	minHeapNode *left, *right;

	minHeapNode(char c, unsigned frequency)
	{
		
	}
};

struct minHeap { //najmniejsza ga��� 
	unsigned size;
	unsigned capacity;
};

struct encoding {

};

struct decoding {

};

class huffman {
private:
	std::map<char, int> freq;
	appSettings* settings;
	minHeapNode minHN;

	//void sort();

public:
	huffman(appSettings* settings) {
		this->settings = settings;
	}
	void sort();
};

//utworzenie struktury danych potrzebnych do stworzenia kodowania i dekodowania drzewa huffmana
//policzenie i posortowanie znak�w