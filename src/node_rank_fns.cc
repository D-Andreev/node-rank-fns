#include "node_rank_fns.h"
#include "ranking_fns/RankingFns.h"
#include "utils/Utils.h"
#include <iostream>
#include "vector"
#include "string"
#include "workers/TfIdfWorker.h"
#include "workers/BM25Worker.h"

NodeRankFns::NodeRankFns(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    double k = 1, b = 0.5;
    if (info[0].IsObject()) {
        Napi::Object options = info[0].As<Napi::Object>();
        k = options.Get("k").As<Napi::Number>().DoubleValue();
        if (k <= 0) {
            Napi::TypeError::New(env, "k parameter must be larger than 0")
                    .ThrowAsJavaScriptException();
            return;
        }
        b = options.Get("b").As<Napi::Number>().DoubleValue();
        if (b < 0 || b > 1) {
            Napi::TypeError::New(env, "b parameter must be between 0 and 1")
                    .ThrowAsJavaScriptException();
            return;
        }
    }

    this->rankingFns = new RankingFns(k, b);
    this->utils = new Utils();
}

/**
 * Get TF-IDF scores
 * @param info [documents file path, terms file path]
 * @returns tf-idf score for each of the documents
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
