#pragma once

#ifndef MAKE_FREQ_SHIFT_H
#define MAKE_FREQ_SHIFT_H
bool MakeFreqShift(const std::vector<std::complex<float>>&data_in,	
	const double freq_shift,	
	std::vector<std::complex<float>>&data_out);
#endif