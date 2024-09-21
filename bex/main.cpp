#include <iostream>
#include <filesystem>

#include "process.h"

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

    int filesModified = 0;
#if __has_include("openssl/sha.h")
#else
    std::cout << "OpenSSL not found! Exiting." << std::endl;
    return 1;
#endif
    std::string path = ".";
    if (argc == 2)
    {
        path = argv[1];
    }
    std::filesystem::path pPath(path);
    if (std::filesystem::is_directory(pPath))
    {
        for (const auto &entry : std::filesystem::directory_iterator(pPath))
        {
            if (entry.is_regular_file())
            {
                std::filesystem::path tempPath(entry);
                if(process(tempPath.c_str())) {
                    ++filesModified;
                }
            }
        }
    }
    else
    {
        if(process(pPath.c_str())) {
            ++filesModified;
        }
    }

    if(filesModified == 0) {
        std::cout << "No files modified" << std::endl;
    } else if(filesModified == 1) {
        std::cout << filesModified << " file modified" << std::endl;
    } else if(filesModified > 1) {
        std::cout << filesModified << " files modified" << std::endl;
    }
    return 0;
}
