//
// Created by ekin4 on 28/04/2017.
//

#ifndef CUSTOMOGL_CALLBACKFUNCTION_H
#define CUSTOMOGL_CALLBACKFUNCTION_H

#include <memory>

/*
 * Acts as a generic wrapper for arbitrary functions.
 * */

namespace cogl {
    template<typename F>
    class FunctionWrapper {
    };

    template<typename F>
    struct helper {
        F *func;
    };

    template<typename T, typename... Args>
    class FunctionWrapper<T(Args...)> {
    private:
        helper<T(Args...)> selfFunc;
    public:
        FunctionWrapper(T (*funcPointer)(Args...)) { selfFunc.func = funcPointer; };

        T operator()(Args... args) { return (*selfFunc.func)(args...); };
    };
}

#endif //CUSTOMOGL_CALLBACKFUNCTION_H
