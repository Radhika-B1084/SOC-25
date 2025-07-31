#ifndef MACD_STRATEGY_H
#define MACD_STRATEGY_H

#include <vector>

std::vector<double> calculate_ema(const std::vector<double>& prices, int span);

void calculate_MACD(
    const std::vector<double>& prices,
    std::vector<double>& MACD,
    std::vector<double>& Signal,
    std::vector<double>& Buy,
    std::vector<double>& Sell
);

#endif
