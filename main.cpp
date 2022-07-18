#include <iostream>
#include "parse.h"


int main(int argc, char* argv[]) {
    parse_string("   %in%+-*/^r'--[i am a raw string]--' while for _ hello");
    parse_string("    %in%");
}
