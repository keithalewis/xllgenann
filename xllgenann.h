// xllgenann.h - genann add-in
#pragma once
#include <stdexcept>
//#define GENANN_RANDOM - uniform [0,1)
#include "genann/genann.h"

namespace xll {

    class genann {
        ::genann* p;
    public:
        genann()
        { }
        genann(int inputs, int hidden_layers, int hidden, int outputs)
            : p(::genann_init(inputs, hidden_layers, hidden, outputs))
        {
            if (!p) {
                throw std::invalid_argument("genann_init failed");
            }
        }
        genann(const genann&) = delete;
        genann& operator=(const genann&) = delete;
        ~genann()
        {
            if (p) {
                ::genann_free(p);
            }
        }
        const ::genann* ptr() const
        {
            return p;
        }
        operator const ::genann*() const
        {
            return p;
        }
    };

}