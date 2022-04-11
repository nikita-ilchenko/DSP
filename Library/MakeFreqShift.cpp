#include "MakeFreqShift.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <algorithm>
#include <cmath>
#include <iostream>

bool MakeFreqShift(const std::vector<ComplexSamples>& data_in,
                   const double freq_shift,
                   std::vector<ComplexSamples>& data_out) {
  using namespace std::complex_literals;
  if (freq_shift >= 1 || freq_shift < 0) {
    std::cout << "Error: freq_shift should be from 0 to 1" << std::endl;
    return 1;
  }
  data_out = data_in;
  for (auto j = 0; j < data_out.size(); ++j) {
    //data_out[j] *= static_cast<std::complex<float>>(
    //    std::exp(1i * static_cast<std::complex<double>>(
    //                      2.0 * M_PI * freq_shift * j)));  // 2.4e7 samples/sec
    data_out[j].realPart =
        data_in[j].realPart * cos(2.0 * M_PI * freq_shift * j) -
        data_in[j].imagPart * sin(2.0 * M_PI * freq_shift * j);
    data_out[j].imagPart =
        data_in[j].realPart * sin(2.0 * M_PI * freq_shift * j) +
        data_in[j].imagPart *
            cos(2.0 * M_PI * freq_shift * j);  // 3.9e7 samples/sec
  }
  return 0;
}