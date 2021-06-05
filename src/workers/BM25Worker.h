#pragma once
#include <napi.h>
#include "../ranking_fns/RankingFns.h"
#include "../utils/Utils.h"

class BM25Worker : public Napi::AsyncWorker {

public:
    BM25Worker(
            Napi::Function& callback,
            RankingFns *rankingFns,
            Utils *utils,
            std::vector<std::string> documents,
            std::vector<std::string> terms
    );
    virtual ~BM25Worker() {};

    void Execute();
    void OnOK();

private:
    std::vector<std::string> documents;
    std::vector<std::string> terms;
    RankingFns *rankingFns;
    Utils *utils;
    std::vector<double> scores;
};