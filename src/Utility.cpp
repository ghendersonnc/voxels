#include "Utility.h"

#include <string>
#include <random>



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

int Voxels::Utility::randomNumber(const long long& seed)
{
    static thread_local std::mt19937 generator;  // NOLINT(cert-msc51-cpp)
    std::uniform_int_distribution distribution(1, 5000);
    return distribution(generator);

}
