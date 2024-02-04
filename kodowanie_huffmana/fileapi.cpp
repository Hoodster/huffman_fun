#include "fileapi.h"

EncodingResult* fileapi::readFromFile(MinHeapNode* root) {
    std::ifstream file(settings.inputFile);
    char* encodedText = nullptr;
    file >> encodedText >> std::endl;
    root = readFromFileRec(root, file);
    file.close();
    return new EncodingResult(encodedText, root);
}

void fileapi::writeEncodingOutputToFile(EncodingResult* result) {
    std::ofstream file(settings.outputFile);
    if (!file.is_open()) {
        std::cerr << "Error while opening file" << std::endl;
        return;
    }
    file << result->encodedText << std::endl;
    writeToFileRec(result->root, file);
	
    file.close();
}

void fileapi::writeDecodingOutputToFile(DecodingResult* result) {
    std::ofstream file(settings.outputFile);
    if (!file.is_open()) {
        std::cerr << "Error while opening file" << std::endl;
        return;
    }

    file << result->decodedText << std::endl;
    file.close();
}

//pobranie node'a z wiersza i przejście dalej do gałęzi potomnych, algorytm to deep first search (DFS)
//powiedz kokotowi to się zesra
MinHeapNode* fileapi::readFromFileRec(MinHeapNode* root, const std::ifstream& file) {
    char* value;
	
    // exit condition
    if (!(file >> value)) {
        return nullptr;
    }

    auto* node = new MinHeapNode(value[0], value[2]);
    node->left = readFromFileRec(root->left, file);
    node->right = readFromFileRec(root->right, file);
    
    return node;
}

// to co wyżej tylko zapisywanie wierszy
void fileapi::writeToFileRec(MinHeapNode* root, const std::ofstream& file) {
    if (root == nullptr) {
        return;
    }

    file << root->character << " " << root->frequency << std::endl;

    writeToFileRec(root->left, file);
    writeToFileRec(root->right, file);
}