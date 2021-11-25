#include <fstream>
#include <iostream>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main(int argc, char const *argv[])
{
    std::string path = "/path/to/directory";
    for (const auto & entry : fs::directory_iterator(path))
    std::cout << entry.path() << std::endl;
    return 0;
}
