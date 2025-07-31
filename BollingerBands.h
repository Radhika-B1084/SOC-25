#ifndef BOLLINGER_H
#define BOLLINGER_H

#include <vector>
#include <string>

std::vector<double> sma(const std::vector<double>& prices, int window);
std::vector<double> std_dev(const std::vector<double>& prices, int window);

void bollinger_bands(const std::vector<double>& prices, int window, double num_std_dev,
                     std::vector<double>& smaa, std::vector<double>& upper_band,
                     std::vector<double>& lower_band, std::vector<std::string>& signal);

#endif