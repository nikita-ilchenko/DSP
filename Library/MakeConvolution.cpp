#include "MakeConvolution.h"

std::vector<ComplexSamples> MakeConvolution(
    const std::vector<ComplexSamples>& first_signal,
    const std::vector<ComplexSamples>& second_signal) {
  int num_samples_after_conv = first_signal.size() + second_signal.size() - 1;
  std::vector<ComplexSamples> signal_after_conv(num_samples_after_conv);
  //std::reverse(second_signal.begin(), second_signal.end());
  for (auto i = 0; i < first_signal.size(); ++i) {
    for (auto j = 0; j < second_signal.size(); ++j) {
      signal_after_conv[i + j].realPart =
          signal_after_conv[i + j].realPart +
          first_signal[i].realPart * second_signal[j].realPart -
          first_signal[i].imagPart * (-second_signal[j].imagPart);
      signal_after_conv[i + j].imagPart =
          signal_after_conv[i + j].imagPart +
          first_signal[i].realPart * (-second_signal[j].imagPart) -
          first_signal[i].imagPart * second_signal[j].realPart;
    }
  }
  return signal_after_conv;
}