#pragma once

#include <napi.h>
#include <map>

class NodeRankFns : public Napi::ObjectWrap<NodeRankFns>
{
public:
    NodeRankFns(const Napi::CallbackInfo&);
    Napi::Value TfIdf(const Napi::CallbackInfo&);

    static Napi::Function GetClass(Napi::Env);

private:
    static std::vector<std::string> NapiArrayToVector(Napi::Array arr);
    static Napi::Array VectorToNapiArray(Napi::Env env, const std::vector<double>& vec);
    static std::vector<std::string> SplitString(const std::string& str);
    static double GetTermFrequency(
            std::vector<std::string> &docs,
            std::vector<std::string> &terms);
    static std::vector<std::string> ParseInputFile(const std::string &documentFilePath);
    double GetDocumentFrequency(
            std::vector<std::string> &document,
            std::vector<std::string> &terms);
    std::vector<double> GetTfIdf(std::vector<std::string> &documents, std::vector<std::string> &terms);
};
