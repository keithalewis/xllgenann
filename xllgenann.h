// xllgenann.h - genann add-in
#pragma once
//#define GENANN_RANDOM - uniform [0,1)
#include "genann/genann.h"

namespace xll {

    class genann {
        ::genann* p;
    public:
        genann(int inputs, int hidden_layers, int hidden, int outputs)
            : p(genann_init(inputs, hidden_layers, hidden, outputs))
        { }
        genann(const genann&) = delete;
        genann& operator=(const genann&) = delete;
        ~genann()
        {
            genann_free(p);
        }
        operator ::genann*() const
        {
            return p;
        }
    };

}