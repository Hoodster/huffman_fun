#include "huffman.h"
#include "parameters.h"
#include "appSettings.h"
#include <map>
#include <queue>
#include <vector>

using namespace std;

void huffman::encode(char d[], int frequency[])
{
	int size = sizeof(d) / sizeof(d[0]);

	priority_queue<MinHeapNode*, vector<MinHeapNode*>> priorityQ;

	for (int i = 0; i < size; i++)
	{
		auto node = new MinHeapNode(d[i],frequency[i]);
		priorityQ.push(node);
	}

	MinHeapNode root = NULL;

	while (priorityQ.size() > 1)
	{
		auto minFreqNode = priorityQ.top();
		priorityQ.pop();
		
		auto secondMinFreqNode = priorityQ.top();
		priorityQ.pop();

		auto combinedFrequency = minFreqNode->frequency + secondMinFreqNode->frequency;
		auto freq_node = new MinHeapNode('-', combinedFrequency);
		freq_node->left = minFreqNode;
		freq_node->right = secondMinFreqNode;

		root = *freq_node;

		priorityQ.push(freq_node);
	}
	
}

bool huffman::compareToRight(MinHeapNode* l, MinHeapNode* r)
{
	return l->frequency > r->frequency;
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
}

