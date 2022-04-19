#pragma once
#ifndef MAKE_CONVOLUTION_H
#define MAKE_CONVOLUTION_H

#include <vector>

struct ComplexSamples {
  float realPart;
  float imagPart;
};

std::vector<ComplexSamples> MakeConvolution(
    const std::vector<ComplexSamples>& first_signal,
    const std::vector<ComplexSamples>& second_signal);
#endif  // MAKE_CONVOLUTION_H