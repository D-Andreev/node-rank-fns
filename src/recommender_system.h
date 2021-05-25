#pragma once

#include <napi.h>
#include "ranking_fns/RankingFns.h"
#include "utils/Utils.h"

class RecommenderSystem : public Napi::ObjectWrap<RecommenderSystem>
{
public:
    RecommenderSystem(const Napi::CallbackInfo&);
    static Napi::Function GetClass(Napi::Env);

    Napi::Value TfIdf(const Napi::CallbackInfo&);
    Napi::Value BM25(const Napi::CallbackInfo &info);

private:
    RankingFns *rankingFns;
    Utils *utils;
};
