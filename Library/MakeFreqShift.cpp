#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>
#include "MakeFreqShift.h"


bool MakeFreqShift(const std::vector<std::complex<float>>& data_in,
	const double freq_shift,
	std::vector<std::complex<float>>& data_out)
{
	using namespace std::complex_literals;
	if (freq_shift >= 1 || freq_shift < 0){
		std::cout << "Error: freq_shift should be from 0 to 1" << std::endl;
		return 1;
	}
	for (int j = 0; j < data_in.size(); ++j) {
		data_out.push_back(data_in[j] * static_cast<std::complex<float>>(std::exp(1i * static_cast<std::complex<double>>(2 * M_PI * freq_shift * j))));
	}
	return 0;
}