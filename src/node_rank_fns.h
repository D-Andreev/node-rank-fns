#pragma once

#include <napi.h>

class NodeRankFns : public Napi::ObjectWrap<NodeRankFns>
{
public:
    NodeRankFns(const Napi::CallbackInfo&);
    Napi::Value TfIdf(const Napi::CallbackInfo&);

    static Napi::Function GetClass(Napi::Env);

private:
    std::vector<std::string> NapiArrayToVector(Napi::Array arr);
    Napi::Array VectorToNapiArray(Napi::Env env, std::vector<std::string> v);
};
