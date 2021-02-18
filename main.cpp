#include <iostream>
#include <string>
#include <fstream>
#include "QS.h"

#define SWAP(a, b) a ^= b; b ^= a; a^=b;

#define BRACEWRAP(func) std::cout << "{"; func; std::cout << "}";
#define TITLE(s) std::cout << " - - - " << s << " - - - " << std::endl;

int main(int argc, char *argv[]){

    QS *qs = new QS();

    TITLE("CREATING AND PRINTING ARRAY FROM ARGS:")
    qs->createArray(argc-1);

    for(int i = 1; i < argc; i++){
        qs->addToArray(std::stoi(argv[i]));
    }

    BRACEWRAP(std::cout << qs->getArray())
    std::cout << std::endl;

    TITLE("SORTING ARRAY")
    qs->sortAll();

    TITLE("SORTED ARRAY")
    BRACEWRAP(std::cout << qs->getArray())

    delete qs;

	return 0;
}
