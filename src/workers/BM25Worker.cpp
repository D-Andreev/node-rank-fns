#include "BM25Worker.h"
#include "../ranking_fns/RankingFns.h"
#include "../utils/Utils.h"
#include <chrono>

BM25Worker::BM25Worker(
        Napi::Function& callback,
        RankingFns *rankingFns,
        Utils *utils,
        std::vector<std::string> documents,
        std::vector<std::string> terms
)
        : AsyncWorker(callback), rankingFns(rankingFns), utils(utils), documents(documents), terms(terms) {};

void BM25Worker::Execute() {
    this->scores = this->rankingFns->GetBM25(documents, terms);
};

void BM25Worker::OnOK() {
    auto result = this->utils->VectorToNapiArray(Env(), this->scores);
    Callback().Call({Env().Null(), result});
};