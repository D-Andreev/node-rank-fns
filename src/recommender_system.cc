#include "recommender_system.h"
#include "ranking_fns/RankingFns.h"
#include "utils/Utils.h"
#include <iostream>
#include "vector"
#include "string"
#include "workers/TfIdfWorker.h"
#include "workers/BM25Worker.h"

RecommenderSystem::RecommenderSystem(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    this->rankingFns = new RankingFns();
    this->utils = new Utils();
}

/**
 * Get TF-IDF scores
 * @param info [documents file path, terms file path]
 * @returns tf-idf score for each of the documents
 * O(N * M) ST (where N is the number of documents and M is the number of terms)
 * O(N) T (where N is the number of documents
 */
Napi::Value RecommenderSystem::TfIdf(const Napi::CallbackInfo& info) {
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
    if (!info[2].IsFunction()) {
        Napi::TypeError::New(env, "callback not valid")
                .ThrowAsJavaScriptException();
        return env.Null();
    }
    auto documents = this->utils->ParseInputFile(info[0].As<Napi::String>().Utf8Value());
    auto terms = this->utils->ParseInputFile(info[1].As<Napi::String>().Utf8Value());

    Napi::Function callback = info[2].As<Napi::Function>();
    TfIdfWorker* asyncWorker = new TfIdfWorker(callback, this->rankingFns, this->utils, documents, terms);
    asyncWorker->Queue();
    return env.Null();
}

/**
 * Get BM25 scores
 * @param info [documents file path, terms file path]
 * @returns bm25 score for each of the documents
 * O(N * M) ST (where N is the number of documents and M is the number of terms)
 * O(N) T (where N is the number of documents
 */
Napi::Value RecommenderSystem::BM25(const Napi::CallbackInfo& info) {
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
    if (!info[2].IsFunction()) {
        Napi::TypeError::New(env, "callback not valid")
                .ThrowAsJavaScriptException();
        return env.Null();
    }

    auto documents = this->utils->ParseInputFile(info[0].As<Napi::String>().Utf8Value());
    auto terms = this->utils->ParseInputFile(info[1].As<Napi::String>().Utf8Value());

    Napi::Function callback = info[2].As<Napi::Function>();
    BM25Worker* asyncWorker = new BM25Worker(callback, this->rankingFns, this->utils, documents, terms);
    asyncWorker->Queue();
    return env.Null();
}

Napi::Function RecommenderSystem::GetClass(Napi::Env env) {
    return DefineClass(env, "RecommenderSystem", {
            RecommenderSystem::InstanceMethod("tfIdf", &RecommenderSystem::TfIdf),
            RecommenderSystem::InstanceMethod("bm25", &RecommenderSystem::BM25),
    });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::String name = Napi::String::New(env, "RecommenderSystem");
    exports.Set(name, RecommenderSystem::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)
