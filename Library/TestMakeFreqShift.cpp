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
  using namespace std::complex_literals;
  const int64_t kNumberOfSamples = 15000000;
  bool result;
  std::vector<std::complex<float>> signal_freq_first(kNumberOfSamples);
  std::vector<std::complex<float>> signal_freq_second(kNumberOfSamples);
  std::vector<float> signal_freq_first_real(kNumberOfSamples);
  std::vector<float> signal_freq_first_imag(kNumberOfSamples);

  // Generating signals with freq1 and freq2
  double freq_first = 0.4;
  double freq_second = 0.8;
  for (int j = 0; j < kNumberOfSamples; ++j) {
    signal_freq_first[j] = cos(2.0 * M_PI * freq_first * j) +
                           1i * sin(2.0 * M_PI * freq_first * j);
    signal_freq_first_real[j] = std::real(signal_freq_first[j]);
    signal_freq_first_imag[j] = std::imag(signal_freq_first[j]);
    signal_freq_second[j] = cos(2.0 * M_PI * freq_second * j) +
                            1i * sin(2.0 * M_PI * freq_second * j);
  }

  // Making shift on freq2-freq1
  std::vector<std::complex<float>> signal_after_shift;
  clock_t start_time = clock();
  result = MakeFreqShift(signal_freq_first, freq_second - freq_first,
                         signal_after_shift);
  clock_t end_time = clock();
  if (result) {
    std::cout << "Error detecting" << std::endl;
  }

  // Difference between signal with f2 frequency and signal after shift
  std::vector<float> signal_after_shift_real(kNumberOfSamples);
  std::vector<float> signal_after_shift_imag(kNumberOfSamples);
  std::vector<float> error_signal(kNumberOfSamples);
  for (int j = 0; j < kNumberOfSamples; ++j) {
    error_signal[j] = std::abs(signal_freq_second[j] - signal_after_shift[j]);
    signal_after_shift_real[j] = std::real(signal_after_shift[j]);
    signal_after_shift_imag[j] = std::imag(signal_after_shift[j]);
  }

  // Writing signals to file for drawing in MATLAB
  //std::ofstream file_data_in(
  //    "DataIn.txt", std::ios::out | std::ios::trunc | std::ios::binary);
  //std::ofstream file_data_out(
  //    "DataOut.txt", std::ios::out | std::ios::trunc | std::ios::binary);
  //if (file_data_in.is_open() && file_data_out.is_open()) {
  //  for (auto j = 0; j < kNumberOfSamples; ++j) {
  //    file_data_in.write(reinterpret_cast<char*>(&signal_freq_first_real[j]),
  //                       sizeof(float));
  //    file_data_in.write(reinterpret_cast<char*>(&signal_freq_first_imag[j]),
  //                       sizeof(float));
  //    file_data_out.write(reinterpret_cast<char*>(&signal_after_shift_real[j]),
  //                        sizeof(float));
  //    file_data_out.write(reinterpret_cast<char*>(&signal_after_shift_imag[j]),
  //                        sizeof(float));
  //  }
  //}
  //file_data_in.close();
  //file_data_out.close();

  float execute_time = (end_time - start_time) / 1000.0f;
  std::cout << "max |y[i]-y'[i]| = "
            << *std::max_element(error_signal.begin(), error_signal.end())
            << std::endl;
  // std::cout << "sigma = "
  //          <<
  std::cout << "Time spent on execution - " << execute_time << " sec"
            << std::endl;
  std::cout.precision(5);
  std::cout << "Speed of operation - "
            << static_cast<float>(kNumberOfSamples) / execute_time
            << " samples/sec" << std::endl;

  return 0;
}