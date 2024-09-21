#include <iostream>
#include <filesystem>

#include "process.h"

int main(int argc, char *argv[])
{
    std::string path = ".";
    if (argc == 2)
    {
        path = argv[1];
    }
    std::filesystem::path pPath(path);
    std::cout << pPath.c_str() << std::endl;
    std::cout << pPath.extension() << std::endl;
    std::cout << pPath.has_extension() << std::endl;
    if (std::filesystem::is_directory(pPath))
    {
        for (const auto &entry : std::filesystem::directory_iterator(pPath))
        {
            if (entry.is_regular_file())
            {
                std::filesystem::path tempPath(entry);
                process(tempPath.c_str());
            }
        }
    }
    else
    {
        std::cout << "Inside single file flow\n";
        process(pPath.c_str());
    }

    return 0;
}
