#ifndef NODE_RANK_FNS_UTILS_H
#define NODE_RANK_FNS_UTILS_H


class Utils {
public:
    Napi::Array VectorToNapiArray(Napi::Env env, const std::vector<double> &vec);
    std::vector<std::string> ParseInputFile(const std::string &filePath);
};


#endif //NODE_RANK_FNS_UTILS_H
