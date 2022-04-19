#include "TestMakeConvolution.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <cmath>
#include <ctime>
#include <iostream>

#include "MakeConvolution.h"

bool TestMakeConvolution() {
  const int64_t kNumberOfSamples = 15000000;
  std::vector<ComplexSamples> first_signal(kNumberOfSamples);
  std::vector<ComplexSamples> second_signal(kNumberOfSamples);

  // Generating signals with freq1 and freq2
  double freq_first = 0.4;
  double freq_second = 0.8;
  for (int j = 0; j < kNumberOfSamples; ++j) {
    first_signal[j].realPart = cos(2.0 * M_PI * freq_first * j);
    first_signal[j].imagPart = sin(2.0 * M_PI * freq_first * j);
    second_signal[j].realPart = cos(2.0 * M_PI * freq_second * j);
    second_signal[j].imagPart = sin(2.0 * M_PI * freq_second * j);
  }

  // Making convolution
  std::vector<ComplexSamples> signal_after_conv;
  clock_t start_time = clock();
  signal_after_conv = MakeConvolution(first_signal, second_signal);
  clock_t end_time = clock();

  float execute_time = (end_time - start_time) / 1000.0f;
  std::cout << "Time spent on execution - " << execute_time << " sec"
            << std::endl;
  std::cout.precision(5);
  std::cout << "Speed of operation - "
            << static_cast<float>(kNumberOfSamples) / execute_time
            << " samples/sec" << std::endl;

  return 0;
}