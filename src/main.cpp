#include <cstdio>
#include "enbin.h"


int main(int argc, char** argv) {
    if (argc != 2) { printf("bad argument count\n"); return 1; }

    EnbinEditor::printEnbinData(argv[1]);
    return 0;
}