#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <limits>

using namespace std;

vector<double> sma(const vector<double>& prices, int window) {
    vector<double> sma(prices.size(), numeric_limits<double>::quiet_NaN());

    for (size_t i = window - 1; i < prices.size(); ++i) {
        double sum = accumulate(prices.begin() + i - window + 1, prices.begin() + i + 1, 0.0);
        sma[i] = sum / window;
    }

    return sma;
}

vector<double> std_dev(const vector<double>& prices, int window) {
    vector<double> std_dev(prices.size(), numeric_limits<double>::quiet_NaN());

    for (size_t i = window - 1; i < prices.size(); ++i) {
        double mean = accumulate(prices.begin() + i - window + 1, prices.begin() + i + 1, 0.0) / window;
        double sum_sq_diff = 0.0;

        for (size_t j = i - window + 1; j <= i; ++j) {
            sum_sq_diff += pow(prices[j] - mean, 2);
        }

        std_dev[i] = sqrt(sum_sq_diff / window);
    }

    return std_dev;
}

void bollinger_bands(const vector<double>& prices, int window, double num_std_dev,
                     vector<double>& smaa, vector<double>& upper_band, vector<double>& lower_band, vector<string>& signal) {
    smaa = sma(prices, window);
    vector<double> stddev = std_dev(prices, window);

    upper_band.resize(prices.size(), numeric_limits<double>::quiet_NaN());
    lower_band.resize(prices.size(), numeric_limits<double>::quiet_NaN());
    signal.resize(prices.size(), "HOLD");

    for (size_t i = 0; i < prices.size(); ++i) {
        if (!isnan(smaa[i]) && !isnan(stddev[i])) {
            upper_band[i] = smaa[i] + num_std_dev * stddev[i];
            lower_band[i] = smaa[i] - num_std_dev * stddev[i];
            
            double margin = 0.5;
            if (abs(prices[i] - lower_band[i]) < margin)
                signal[i] = "BUY";
            else if (abs(prices[i] - upper_band[i]) < margin)
                signal[i] = "SELL";
        }
    }
}
