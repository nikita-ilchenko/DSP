#pragma once
#ifndef MAKE_FREQ_SHIFT_H
#define MAKE_FREQ_SHIFT_H

#include <vector>

struct ComplexSamples {
  float realPart;
  float imagPart;
};

bool MakeFreqShift(const std::vector<ComplexSamples>& data_in,
                   const double freq_shift,
                   std::vector<ComplexSamples>& data_out);

#endif  // MAKE_FREQ_SHIFT_H