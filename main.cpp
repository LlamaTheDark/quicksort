#include <iostream>
#include <string>
#include <fstream>
#include "QS.h"

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

    TITLE("NOW MAKING NULL...")

    qs->clear();

    TITLE("NEW ARRAY:")
    BRACEWRAP(std::cout << qs->getArray())

	return 0;
}
