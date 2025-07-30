#pragma once
using namespace xenon;
#include <functional>

class BaseState {
    public:
        BaseState() {}
        virtual ~BaseState() = default;

        virtual void init(Context& ctx) = 0;
        virtual void update(Context& ctx) = 0;
        virtual void render(Context& ctx) = 0;
        virtual void finish() = 0;
};