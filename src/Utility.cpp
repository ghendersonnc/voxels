#include "Utility.h"

#include <string>

std::string Voxels::Utility::loadIntoString(const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(contents.data(), contents.size());
        in.close();

    return contents;
    }
    throw errno;
}
