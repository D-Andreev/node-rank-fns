#include "node_rank_fns.h"
#include <iostream>
#include "vector"
#include "string"
#include "map"
#include <math.h>
#include <fstream>
#include <sstream>

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

std::vector<std::string> NodeRankFns::ParseInputFile(const std::string &filePath) {
    std::vector<std::string> result;

    std::ifstream file(filePath);
    if (!file.good()) return result;
    std::string str;
    while (getline(file, str)) {
        result.push_back(str);
    }

    return result;
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

std::vector<double> NodeRankFns::GetTfIdf(std::vector<std::string> &documents, std::vector<std::string> &terms) {
    double df = this->GetDocumentFrequency(documents, terms);
    std::vector<double> scores;
    for (auto i = 0; i < documents.size(); i++) {
        auto doc = documents[i];
        auto words = this->SplitString(doc);
        double tf = this->GetTermFrequency(words, terms);
        double idf = log10((double)documents.size() / df);
        scores.push_back(abs(tf * idf));
    }

    return scores;
}

std::vector<double> NodeRankFns::GetBM25(std::vector<std::string> &documents, std::vector<std::string> &terms) {
    double df = this->GetDocumentFrequency(documents, terms);
    std::vector<double> scores;
    int documentLengthSum = 0;
    int n = documents.size();
    for (auto & document : documents) {
        documentLengthSum += document.size();
    }
    double averageDocumentLength = (double)documentLengthSum / n;
    double k = 1;
    double b = 0.5;
    for (const auto& doc : documents) {
        double documentLength = doc.size();
        auto words = this->SplitString(doc);
        double tf = this->GetTermFrequency(words, terms);
        // Fancy tf accounts for term saturation and document length.
        double fancyTf = tf / (tf + k * (1 - b + b * documentLength / averageDocumentLength));
        // Fancy (not so fancy) idf considers less a term if it's in most of the documents.
        double fancyIdf = log10(1 + (n - df + .5) / (df + .5));
        scores.push_back(abs(fancyTf * fancyIdf));
    }

    return scores;
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

    auto documents = this->ParseInputFile(info[0].As<Napi::String>().Utf8Value());
    auto terms = this->ParseInputFile(info[1].As<Napi::String>().Utf8Value());

    auto scores = this->GetTfIdf(documents, terms);
    auto result = this->VectorToNapiArray(env, scores);

    return reinterpret_cast<Napi::Value &&>(result);
}

/**
 * Get BM25 scores
 * @param info [documents file path, terms file path]
 * @returns tf-idf score for each of the documents
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

    auto documents = this->ParseInputFile(info[0].As<Napi::String>().Utf8Value());
    auto terms = this->ParseInputFile(info[1].As<Napi::String>().Utf8Value());

    auto scores = this->GetBM25(documents, terms);
    auto result = this->VectorToNapiArray(env, scores);

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
