#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <ctime>

#define _USE_MATH_DEFINES
#include <math.h>

#include "MakeFreqShift.h"


bool test_MakeFreqShift()
{
	using namespace std::complex_literals;
	double f1 = 0.4;
	double f2 = 0.8;
	long int numSamples = 15000000;
	bool result;
	std::vector<std::complex<float>> data_in;
	std::vector<std::complex<float>> data_test;
	std::vector<std::complex<float>> data_out;
	std::vector<float> data_in_re;
	std::vector<float> data_in_im;
	std::vector<float> data_out_re;
	std::vector<float> data_out_im;
	std::vector<float> diff;

	// Generating signals with f1 and f2 frequencies
	for (int j = 0; j < numSamples; ++j) {
		data_in.push_back(static_cast<std::complex<float>>(std::exp(1i * static_cast<std::complex<double>>(2 * M_PI * f1 * j))));
		data_in_re.push_back(std::real(data_in[j]));
		data_in_im.push_back(std::imag(data_in[j]));
		data_test.push_back(static_cast<std::complex<float>>(std::exp(1i * static_cast<std::complex<double>>(2 * M_PI * f2 * j))));
	}

	// Making shift on f2-f1
	unsigned int start_time = clock();
	result = MakeFreqShift(data_in, f2 - f1, data_out);
	unsigned int end_time = clock();
	if (result) {
		std::cout << "Error detecting" << std::endl;
	}

	// Difference between test signal with f2 frequency and signal after shift
	for (int j = 0; j < numSamples; ++j) {
		diff.push_back(std::abs(data_test[j] - data_out[j]));
		data_out_re.push_back(std::real(data_out[j]));
		data_out_im.push_back(std::imag(data_out[j]));
	}

	// Writing signals to file for drawing in MATLAB
	/*std::ofstream fileInData("DataIn.txt", std::ios::out | std::ios::trunc | std::ios::binary);
	std::ofstream fileOutData("DataOut.txt", std::ios::out | std::ios::trunc | std::ios::binary);
	if (fileInData.is_open() && fileOutData.is_open()) {
		for (int j = 0; j < numSamples; ++j) {
			fileInData.write(reinterpret_cast<char*>(&data_in_re[j]), sizeof(float));
			fileInData.write(reinterpret_cast<char*>(&data_in_im[j]), sizeof(float));
			fileOutData.write(reinterpret_cast<char*>(&data_out_re[j]), sizeof(float));
			fileOutData.write(reinterpret_cast<char*>(&data_out_im[j]), sizeof(float));
		}
	}
	fileInData.close();
	fileOutData.close();*/

	double search_time = (end_time - start_time) / 1000.0;
	std::cout << "max |y[i]-y'[i]| = " << *std::max_element(diff.begin(), diff.end()) << std::endl;
	std::cout << "Time spent on execution - " << search_time << " sec" << std::endl;
	std::cout.precision(5);
	std::cout << "Speed of operation - " << static_cast<float>(numSamples) / search_time << " samples/sec" << std::endl;

	return 0;
}