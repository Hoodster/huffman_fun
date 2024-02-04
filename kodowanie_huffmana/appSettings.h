#pragma once
#include <string>

enum mode {
	encoding,
	decoding
};

struct appSettings {
	char* inputFile;
	char* outputFile;
	mode operationMode;
	std::string text;
};