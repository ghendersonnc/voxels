#pragma once
#include <string>
#include <fstream>

namespace Voxels::Utility {
    std::string loadIntoString(const std::string& filename);
    int randomNumber(const long long& seed);
}