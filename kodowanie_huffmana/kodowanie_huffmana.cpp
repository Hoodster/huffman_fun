
// kodowanie_huffmana.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include "appSettings.h"
#include "parameters.h"
#include "huffman.h"

int main(int argc, char **argv) {
    appSettings settings;
    parameters paramService = parameters(&settings, argc, argv);
    paramService.getSettings();
    huffman huffmancode = huffman(&settings);
    //paramService.readInputFile();  
    huffmancode.sortInput();

    return 0;
}

//wyliczenie ka¿dego symbolu i jego licznosci (done)
//Utworzenie struktury danych