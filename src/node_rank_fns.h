#pragma once

#include <napi.h>
#include "ranking_fns/RankingFns.h"
#include "utils/Utils.h"

class NodeRankFns : public Napi::ObjectWrap<NodeRankFns>
{
public:
    NodeRankFns(const Napi::CallbackInfo&);
    static Napi::Function GetClass(Napi::Env);

    Napi::Value TfIdf(const Napi::CallbackInfo&);
    Napi::Value BM25(const Napi::CallbackInfo &info);

private:
    RankingFns *rankingFns;
    Utils *utils;
};
