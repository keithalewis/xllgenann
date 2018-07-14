// xllgenann.cpp
#include "xllgenann.h"
#include "xll/xll.h"

using namespace xll;

AddIn xai_genann(
    Function(XLL_HANDLE, L"?xll_genann", L"GENANN")
    .Arg(XLL_LONG, L"inputs", L"is the number of inputs.")
    .Arg(XLL_LONG, L"hidden_layers", L"is the number of hidden layers.")
    .Arg(XLL_LONG, L"hidden", L"is the number of neurons.")
    .Arg(XLL_LONG, L"outputs", L"is the number of outputs.")
    .Uncalced()
    .Category(L"GENANN")
    .FunctionHelp(L"Create a genann object.")
);
HANDLEX WINAPI xll_genann(int inputs, int hidden_layers, int hidden, int outputs)
{
#pragma XLLEXPORT
    handlex h;

    try {
        handle<xll::genann> h_(new xll::genann(inputs, hidden_layers, hidden, outputs));
        h = h_.get();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}

AddIn xai_genann_train(
    Function(XLL_HANDLE, L"?xll_genann_train", L"GENANN.TRAIN")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a genann object.")
    .Arg(XLL_FP, L"inputs", L"is the number of inputs.")
    .Arg(XLL_FP, L"outputs", L"is the number of outputs.")
    .Arg(XLL_DOUBLE, L"rate", L"is the learning rate.")
    .FunctionHelp(L"Train a genann object.")
);
HANDLEX WINAPI xll_genann_train(HANDLEX h, _FP12* inputs, _FP12* outputs, double rate)
{
#pragma XLLEXPORT
    try {
        handle<xll::genann> h_(h);
        ensure(h_);
        // ensure input and output size is correct
        int inp;
        inp = h_->inputs;
        ensure(size(*inputs) == 1);// h_->inputs);
        genann_train(*h_, inputs->array, outputs->array, rate);
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());

        h = handlex{};
    }

    return h;
}

// genann_run

AddIn xai_genann_run(
    Function(XLL_HANDLE, L"?xll_genann_run", L"GENANN.RUN")
    .Arg(XLL_HANDLE, L"handle", L"is a handle to a genann object.")
    .Arg(XLL_FP, L"inputs", L"is the number of inputs.")
    .FunctionHelp(L"run a genann object.")
);
HANDLEX WINAPI xll_genann_run(HANDLEX h, _FP12* inputs)
{
#pragma XLLEXPORT
    try {
        handle<xll::genann> h_(h);
        ensure(h_);
        // ensure inputsize is correct
        genann_run(*h_, inputs->array);
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());

        h = handlex{};
    }

    return h;
}
