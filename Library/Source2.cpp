template <typename T, typename... FreqList>
std::vector<T> GenerateTestSin(const size_t samples_num, const double ampl,
                               const double phase_init,
                               FreqList... freq_rel_list) {
  //подготовка - убираем несущие за пределами [-0.5; 0.5]
  std::vector<T> test_sin(samples_num);
  std::vector<double> phase_rel_array = {freq_rel_list...};

  phase_rel_array.erase(
      std::remove_if(phase_rel_array.begin(), phase_rel_array.end(),
                     [](const double freq_rel_curr) {
                       return std::abs(freq_rel_curr) >= 0.5;
                     }),
      phase_rel_array.end());

  for (auto& phase_rel : phase_rel_array) phase_rel *= 2.0 * M_PI;

  //вычисления
  for (size_t samples_ctr = 0; samples_ctr < samples_num; samples_ctr++) {
    for (const auto phase_rel : phase_rel_array) {
      const double phase_curr = phase_rel * (double)samples_ctr + phase_init;

      test_sin[samples_ctr].re += ampl * std::cos(phase_curr);
      test_sin[samples_ctr].im += ampl * std::sin(phase_curr);
    }
  }
  return test_sin;
}