#include "TfIdfWorker.h"
#include "../ranking_fns/RankingFns.h"
#include "../utils/Utils.h"
#include <chrono>

TfIdfWorker::TfIdfWorker(
        Napi::Function& callback,
        RankingFns *rankingFns,
        Utils *utils,
        std::vector<std::string> documents,
        std::vector<std::string> terms
        )
        : AsyncWorker(callback), rankingFns(rankingFns), utils(utils), documents(documents), terms(terms) {};

void TfIdfWorker::Execute() {
    this->scores = this->rankingFns->GetTfIdf(documents, terms);
};

void TfIdfWorker::OnOK() {
    auto result = this->utils->VectorToNapiArray(Env(), this->scores);
    Callback().Call({Env().Null(), result});
};