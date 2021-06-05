#pragma once
#include <napi.h>
#include "../ranking_fns/RankingFns.h"
#include "../utils/Utils.h"

class TfIdfWorker : public Napi::AsyncWorker {

public:
    TfIdfWorker(
            Napi::Function& callback,
            RankingFns *rankingFns,
            Utils *utils,
            std::vector<std::string> documents,
            std::vector<std::string> terms
    );
    virtual ~TfIdfWorker() {};

    void Execute();
    void OnOK();

private:
    std::vector<std::string> documents;
    std::vector<std::string> terms;
    RankingFns *rankingFns;
    Utils *utils;
    std::vector<double> scores;
};