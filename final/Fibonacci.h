#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <vector>
#include <string>

std::vector<double> fibonacci_levels(const std::vector<double>& prices);
std::string get_signal(double price, const std::vector<double>& levels);

#endif
