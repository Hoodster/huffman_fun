#include "parameters.h"


bool parameters::InputFileName(char* argument, std::string i, char* fileName)
{
    if (argument == i) {

        std::ifstream inputFile(fileName);

        if (inputFile.good()) {

            return true;
        }
        std::cout << "plik wejsciowy nie istnieje\n";
    }
    return false;
}

bool parameters::OutputFileName(char* argument, std::string o, char* fileName)
{
    if (argument == o) {

        std::ofstream outputFile(fileName);

        return outputFile.good();
    }
    return false;
}

bool parameters::isInputFileEmpty(const char* fileName)
{
    std::ifstream file(fileName);
    return file.peek() == std::ifstream::traits_type::eof();
}

void parameters::getInputFile(char* argument, char* fileName) {
    std::string i = "-i";
     
    if (InputFileName(argument, i, fileName)) {
        this->settings->inputFile = fileName;
        if (!isFileTxt(fileName)) {
            std::cout << "zle rozszerzenie pliku\n";
            return;
        }
        if (isInputFileEmpty(fileName)) {
           std::cout << "pusty plik wejsciowy\n";
           return;
        }
    }
}

void parameters::getOutputFile(char* argument, char* fileName) {
    std::string o = "-o";
    
    if (OutputFileName(argument, o, fileName)) {
        this->settings->outputFile = fileName;
        if (!isFileTxt(fileName)) {
            std::cout << "zle rozszerzenie pliku";
            return;
        }
    }
    
}

void parameters::getAlgorithmMode(char* argument, bool* paramIsActive) {

    std::string c = "-c";
    std::string d = "-d";

    if (argument == c || argument == d) {
        if (*paramIsActive) {
            std::cout << "niepoprawny parametr wyniku \n";
            throw;
        }
        if (argument == c) {
            this->settings->operationMode = encoding;
        }
        else {
            this->settings->operationMode = decoding;
        }
        
        *paramIsActive = true;
    }
}

bool parameters::isArgCountValid() {
    return numberOfArguments == 6;
}

bool parameters::isFileTxt(char* fileName) {
   std::string fn = fileName;
    return fn.substr(fn.find_last_of(".") + 1) == "txt";
}

void parameters::getSettings() {
    bool paramIsActive = false;

    if (!isArgCountValid()) {
        std::cout << "Nieprawidlowa liczba argumentow \n";
        return;
    }

    for (int i = 1; i < numberOfArguments; i++) {
        try {
            getAlgorithmMode(params[i], &paramIsActive);
            if (i < numberOfArguments - 1) {
                getInputFile(params[i], params[i + 1]);
                getOutputFile(params[i], params[i + 1]);
            }
        }
        catch (...) {
            return;
        }
    }
}

std::string parameters::readInputFile()
{
    std::string dane;
    std::ifstream readInput(this->settings->inputFile);
    
    if (readInput.is_open()) {
        while (readInput) {
            dane = readInput.get();
            std::cout << dane;
        }
    }
        readInput.close();
      return dane;
}
