#include <iostream>

#include "run.h"

int main(int argc, char *argv[])
{
    std::cout << "888888b.\n";
    std::cout << "888  \"88b\n";
    std::cout << "888  .88P\n";
    std::cout << "8888888K.   .d88b.  888  888\n";
    std::cout << "888  \"Y88b d8P  Y8b `Y8bd8P'\n";
    std::cout << "888    888 88888888   X88K\n";
    std::cout << "888   d88P Y8b.     .d8\"\"8b.\n";
    std::cout << "8888888P\"   \"Y8888  888  888\n";

#if __has_include("openssl/sha.h")
#else
    std::cout << "OpenSSL not found! Exiting." << std::endl;
    return 1;
#endif

    run(argc, argv);
    return 0;
}
