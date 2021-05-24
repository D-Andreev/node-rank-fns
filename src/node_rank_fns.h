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
    double GetDocumentFrequency(
            std::vector<std::string> &document,
            std::vector<std::string> &terms);
    std::vector<double> GetTfIdf(Napi::Array documentsInput, Napi::Array termsInput);
};
