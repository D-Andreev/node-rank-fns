#include "node_rank_fns.h"
#include "ranking_fns/RankingFns.h"
#include "utils/Utils.h"
#include <iostream>
#include "vector"
#include "string"

NodeRankFns::NodeRankFns(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    this->rankingFns = new RankingFns();
    this->utils = new Utils();
}

/**
 * Get TF-IDF scores
 * @param info [documents file path, terms file path]
 * @returns tf-idf score for each of the documents
 * @example nodeRankFns.tfIdf('./documents/file/path.txt', './terms/file/path.txt')
 * O(N * M) ST (where N is the number of documents and M is the number of terms)
 * O(N) T (where N is the number of documents
 */
Napi::Value NodeRankFns::TfIdf(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Wrong number of arguments")
                .ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Documents file path is not valid")
                .ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[1].IsString()) {
        Napi::TypeError::New(env, "Terms file path is not valid")
                .ThrowAsJavaScriptException();
        return env.Null();
    }

    auto documents = this->utils->ParseInputFile(info[0].As<Napi::String>().Utf8Value());
    auto terms = this->utils->ParseInputFile(info[1].As<Napi::String>().Utf8Value());

    auto scores = this->rankingFns->GetTfIdf(documents, terms);
    auto result = this->utils->VectorToNapiArray(env, scores);

    return reinterpret_cast<Napi::Value &&>(result);
}

/**
 * Get BM25 scores
 * @param info [documents file path, terms file path]
 * @returns bm25 score for each of the documents
 * @example nodeRankFns.bm25('./documents/file/path.txt', './terms/file/path.txt')
 * O(N * M) ST (where N is the number of documents and M is the number of terms)
 * O(N) T (where N is the number of documents
 */
Napi::Value NodeRankFns::BM25(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Wrong number of arguments")
                .ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Documents file path is not valid")
                .ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[1].IsString()) {
        Napi::TypeError::New(env, "Terms file path is not valid")
                .ThrowAsJavaScriptException();
        return env.Null();
    }

    auto documents = this->utils->ParseInputFile(info[0].As<Napi::String>().Utf8Value());
    auto terms = this->utils->ParseInputFile(info[1].As<Napi::String>().Utf8Value());

    auto scores = this->rankingFns->GetBM25(documents, terms);
    auto result = this->utils->VectorToNapiArray(env, scores);

    return reinterpret_cast<Napi::Value &&>(result);
}

Napi::Function NodeRankFns::GetClass(Napi::Env env) {
    return DefineClass(env, "NodeRankFns", {
        NodeRankFns::InstanceMethod("tfIdf", &NodeRankFns::TfIdf),
        NodeRankFns::InstanceMethod("bm25", &NodeRankFns::BM25),
    });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::String name = Napi::String::New(env, "NodeRankFns");
    exports.Set(name, NodeRankFns::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)
