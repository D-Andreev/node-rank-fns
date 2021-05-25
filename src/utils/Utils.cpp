#include <napi.h>
#include "Utils.h"

#include <fstream>
#include <sstream>

Napi::Array Utils::VectorToNapiArray(Napi::Env env, const std::vector<double>& vec) {
    Napi::Array result = Napi::Array::New(env);

    for (auto i = 0; i < vec.size(); i++) {
        result[i] = vec[i];
    }

    return result;
}

std::vector<std::string> Utils::ParseInputFile(const std::string &filePath) {
    std::vector<std::string> result;

    std::ifstream file(filePath);
    if (!file.good()) return result;
    std::string str;
    while (getline(file, str)) {
        result.push_back(str);
    }

    return result;
}
