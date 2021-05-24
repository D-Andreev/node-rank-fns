#include "node_rank_fns.h"
#include <iostream>
#include "vector"
#include "string"
#include "map"
#include <cmath>

template<typename T>
struct tfIdfScore : public std::vector<T> {};

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

std::vector<std::string> NodeRankFns::SplitString(const std::string& str) {
    std::vector<std::string> res;
    std::string tmp;
    for (char i : str) {
        if (i == ' ') {
            res.push_back(tmp);
            tmp = "";
            continue;
        }

        tmp.push_back(i);
    }
    res.push_back(tmp);

    return res;
}

Napi::Array NodeRankFns::VectorToNapiArray(Napi::Env env, const std::vector<double>& vec) {
    Napi::Array result = Napi::Array::New(env);

    for (auto i = 0; i < vec.size(); i++) {
        result[i] = vec[i];
    }

    return result;
}

double NodeRankFns::GetTermFrequency(std::vector<std::string> &document, std::vector<std::string> &terms) {
    double tfSum = 0;
    for (auto & term : terms) {
        double tf = 0;
        for (auto & word : document) {
            if (term == word) {
                tf++;
            }
        }
        tfSum += tf / document.size();
    }

    return tfSum;
}

double NodeRankFns::GetDocumentFrequency(std::vector<std::string> &docs, std::vector<std::string> &terms) {
    double df = 0;
    for (auto & doc : docs) {
        auto words = this->SplitString(doc);
        bool termExists = false;
        for (auto & term : terms) {
            for (auto & word : words) {
                if (term == word) {
                    termExists = true;
                    break;
                }
            }
            if (termExists) break;
        }
        if (termExists) {
            df++;
        }
    }

    return df;
}

std::vector<double> NodeRankFns::GetTfIdf(Napi::Array documentsInput, Napi::Array termsInput) {
    auto docs = this->NapiArrayToVector(documentsInput);
    auto terms = this->NapiArrayToVector(termsInput);

    double df = this->GetDocumentFrequency(docs, terms);
    std::vector<double> scores;
    for (auto i = 0; i < docs.size(); i++) {
        auto doc = docs[i];
        auto words = this->SplitString(doc);
        double tf = this->GetTermFrequency(words, terms);
        double idf = log10((double)docs.size() / df);
        scores.push_back(abs(tf * idf));
    }

    return scores;
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

    auto scores = this->GetTfIdf(info[0].As<Napi::Array>(), info[1].As<Napi::Array>());
    auto result = this->VectorToNapiArray(env, scores);

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
