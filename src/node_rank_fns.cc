#include "node_rank_fns.h"
#include <iostream>
#include "vector"
#include "string"

NodeRankFns::NodeRankFns(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
}

std::vector<std::string> NodeRankFns::NapiArrayToVector(Napi::Array arr) {
    std::vector<std::string> v;
    for (auto i = 0; i < arr.Length(); i++) {
        v.emplace_back(static_cast<Napi::Value>(arr[i]).ToString().Utf8Value());
    }

    return v;
}

Napi::Array NodeRankFns::VectorToNapiArray(Napi::Env env, std::vector<std::string> v) {
    Napi::Array result = Napi::Array::New(env);

    for (auto i = 0; i < v.size(); i++) {
        result[i] = v[i];
    }

    return result;
}

Napi::Value NodeRankFns::TfIdf(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Wrong number of arguments")
                .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsArray()) {
        Napi::TypeError::New(env, "Documents array is not valid")
                .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[1].IsArray()) {
        Napi::TypeError::New(env, "Terms array is not valid")
                .ThrowAsJavaScriptException();
        return env.Null();
    }

    auto docs = this->NapiArrayToVector(info[0].As<Napi::Array>());
    auto terms = this->NapiArrayToVector(info[1].As<Napi::Array>());
    auto result = this->VectorToNapiArray(env, docs);

    return reinterpret_cast<Napi::Value &&>(result);
}

Napi::Function NodeRankFns::GetClass(Napi::Env env) {
    return DefineClass(env, "NodeRankFns", {
        NodeRankFns::InstanceMethod("tfIdf", &NodeRankFns::TfIdf),
    });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::String name = Napi::String::New(env, "NodeRankFns");
    exports.Set(name, NodeRankFns::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)
