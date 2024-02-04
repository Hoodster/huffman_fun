#pragma once
#include "huffman.h"

class fileapi
{
private:
    appSettings settings;
    
    MinHeapNode* readFromFileRec(MinHeapNode* root, const std::ifstream& file);
    void writeToFileRec(MinHeapNode* root, const std::ofstream& file);
public:
    explicit fileapi(appSettings settings) {
        this->settings = settings;
    }
    
    EncodingResult* readFromFile(MinHeapNode* root);
    void writeEncodingOutputToFile(EncodingResult* result);
    void writeDecodingOutputToFile(DecodingResult* result);
};
