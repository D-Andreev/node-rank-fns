#pragma once

#include <napi.h>

class NodeRankFns : public Napi::ObjectWrap<NodeRankFns>
{
public:
    NodeRankFns(const Napi::CallbackInfo&);
    Napi::Value Greet(const Napi::CallbackInfo&);

    static Napi::Function GetClass(Napi::Env);

private:
    std::string _greeterName;
};
