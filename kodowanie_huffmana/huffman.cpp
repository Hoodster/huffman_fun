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

	priority_queue<MinHeapNode*, vector<MinHeapNode*> >priorityQ;

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

void huffman::sort() {

	std::ifstream input(settings->inputFile);

	if (input) {
		char data;
		std::map<char, int> freq;
		while (input.get(data) {
		while (input.get(data)) {
			freq[data]++;
		}
		input.close();

		for (const auto& wpis : freq) {
			std::cout << wpis.first << "   " << wpis.second << std::endl
			std::cout << wpis.first << "   " << wpis.second << std::endl;
		}
	}
}

