#include "TestMakeFreqShift.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <numeric>

#include "MakeFreqShift.h"

bool TestMakeFreqShift() {
  //using namespace std::complex_literals;
  const int64_t kNumberOfSamples = 15000000;
  bool fail;
  std::vector<ComplexSamples> signal_freq_first(kNumberOfSamples);
  std::vector<ComplexSamples> signal_freq_second(kNumberOfSamples);
  //std::vector<float> signal_freq_first_real(kNumberOfSamples);
  //std::vector<float> signal_freq_first_imag(kNumberOfSamples);

  // Generating signals with freq1 and freq2
  double freq_first = 0.4;
  double freq_second = 0.8;
  for (int j = 0; j < kNumberOfSamples; ++j) {
    signal_freq_first[j].realPart = cos(2.0 * M_PI * freq_first * j);
    signal_freq_first[j].imagPart = sin(2.0 * M_PI * freq_first * j);
    //signal_freq_first_real[j] = std::real(signal_freq_first[j]);
    //signal_freq_first_imag[j] = std::imag(signal_freq_first[j]);
    signal_freq_second[j].realPart = cos(2.0 * M_PI * freq_second * j);
    signal_freq_second[j].imagPart = sin(2.0 * M_PI * freq_second * j);
  }

  // Making shift on freq2-freq1
  std::vector<ComplexSamples> signal_after_shift;
  clock_t start_time = clock();
  fail = MakeFreqShift(signal_freq_first, freq_second - freq_first,
                         signal_after_shift);
  clock_t end_time = clock();
  if (fail) {
    std::cout << "Error detecting" << std::endl;
    return 1;
  }

  // Difference between signal with f2 frequency and signal after shift
  //std::vector<float> signal_after_shift_real(kNumberOfSamples);
  //std::vector<float> signal_after_shift_imag(kNumberOfSamples);
  std::vector<float> error_signal_abs(kNumberOfSamples);
  for (int j = 0; j < kNumberOfSamples; ++j) {
    error_signal_abs[j] = std::sqrt(std::pow(signal_freq_second[j].realPart -
                                                 signal_after_shift[j].realPart, 2) +
                                    std::pow(signal_freq_second[j].imagPart -
                                                 signal_after_shift[j].imagPart, 2));
    // signal_after_shift_real[j] = std::real(signal_after_shift[j]);
    // signal_after_shift_imag[j] = std::imag(signal_after_shift[j]);
  }

  float execute_time = (end_time - start_time) / 1000.0f;
  std::cout << "max |y[i]-y'[i]| = "
            << *std::max_element(error_signal_abs.begin(),
                                 error_signal_abs.end())
            << std::endl;
  std::cout << "Time spent on execution - " << execute_time << " sec"
            << std::endl;
  std::cout.precision(5);
  std::cout << "Speed of operation - "
            << static_cast<float>(kNumberOfSamples) / execute_time
            << " samples/sec" << std::endl;

  return 0;
}