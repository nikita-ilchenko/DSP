bool RiscDspTester::TestFreqShifter(const double freq_center_rel_req) {
  const int samples_num =
      risc_dsp::DspGraph::GetBlockSize() *
      20;  //тестирование на 10 блоках, чтобы проверить сшивку
  const double ampl = 5000.0;
  const double freq_sig_rel_in = 0.001;  //просто выставляем рандомную несущую,
                                         //чтобы исключить тривиальность теста
  const double freq_sig_rel_out =
      freq_sig_rel_in -
      freq_center_rel_req;  //если в качестве новой центральной потока -
                            //положительное число, то сигнал сместится влево и
                            //наоборот
  const double sample_rate_hz = 1000'000.0;
  const double phase_init = M_PI_4;
  const double freq_center_hz_in = 0.0;
  const double freq_center_hz_req = freq_center_rel_req * sample_rate_hz;

  const std::vector<Dsp16sc> signal_in =
      GenerateTestSin<Dsp16sc>(samples_num, ampl, phase_init, freq_sig_rel_in);
  const std::vector<Dsp32fc> signal_out =
      GenerateTestSin<Dsp32fc>(samples_num, ampl, phase_init, freq_sig_rel_out);

  //инициализация конвейера
  const clock_t time_start = clock();
  const auto data_source = std::make_shared<risc_dsp::SourceNode<Dsp16sc>>(
      signal_in.data(), signal_in.size(), sample_rate_hz, freq_center_hz_in);
  auto dsp_graph = std::make_shared<risc_dsp::DspGraph>(data_source);
  std::vector<Dsp32fc> signal_res;

  dsp_graph->AddNode(std::make_shared<risc_dsp::FreqShifterNode>(
      freq_center_hz_in, freq_center_hz_req, sample_rate_hz));

  if (!dsp_graph->GetSignalBlock({}, signal_res)) return false;

  //время выполнения
  const clock_t time_end = clock();
  const uint64_t test_time =
      (uint64_t)(time_end - time_start) * uint64_t(1000) / CLOCKS_PER_SEC;

  std::cout << "   Elapsed time: " << test_time << " ms" << std::endl;

  test_clocks_num_ += (uint64_t)(time_end - time_start);

  //проверка результата
  return CheckSignalsCorr(signal_out, signal_res, true);
}