#include "appSettings.h"
#include <string>
#include <iostream>
#include <fstream>

class parameters {
private:
	appSettings* settings;
	int numberOfArguments;
	char** params;

	bool InputFileName(char* argument, std::string i, char* fileName);

	bool OutputFileName(char* argument, std::string o, char* fileName);

	bool isInputFileEmpty(const char* fileName);

	void getInputFile(char* argument, char* fileName);

	void getOutputFile(char* argument, char* fileName);

	void getAlgorithmMode(char* argument, bool* paramIsActive);

	bool isArgCountValid();

	bool isFileTxt(char* fileName);
	
public:
	parameters(appSettings* appSettings, int numberOfArguments, char** params) {
		this->settings = appSettings;
		this->numberOfArguments = numberOfArguments;
		this->params = params;
	}

	void getSettings();

	std::string readInputFile();
};
