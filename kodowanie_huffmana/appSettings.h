#pragma once

enum mode {
	encoding,
	decoding
};

struct appSettings {
	char* inputFile;
	char* outputFile;
	mode operationMode;
};