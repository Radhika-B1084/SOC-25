#include <vector>
#include <iostream>
#include <limits>
using namespace std;

vector<double> calculate_ema(const vector<double>& prices, int span) {
    vector<double> ema_values;

    if (prices.empty() || span <= 0)
        return ema_values;

    double alpha = 2.0 / (span + 1);  

    double ema = prices[0];
    ema_values.push_back(ema);

    for (size_t i = 1; i < prices.size(); ++i) {
        ema = alpha * prices[i] + (1.0 - alpha) * ema;
        ema_values.push_back(ema);
    }
    return ema_values;
}

void calculate_MACD(const vector<double>& prices, vector<double>& MACD, vector<double>& Signal, vector<double>& Buy, vector<double>& Sell){
    
    vector<double> short_ema = calculate_ema(prices, 12);
    vector<double> long_ema = calculate_ema(prices, 26);
    
    MACD.clear();
    size_t min_size = min(short_ema.size(), long_ema.size());
    for (size_t i = 0; i < min_size; ++i) {
        MACD.push_back(short_ema[i] - long_ema[i]);
    }
    
    Signal = calculate_ema(MACD, 9);
    
    int flag = -1;
    for (size_t i = 0; i < min_size; ++i){
        if (MACD[i] > Signal[i]){
            Sell.push_back(numeric_limits<double>::quiet_NaN());
            if (flag!=-1){
                Buy.push_back(prices[i]);
                flag = 1;
            }
            else{
                Buy.push_back(numeric_limits<double>::quiet_NaN());
            }
        }
        else if (MACD[i] < Signal[i]){
            Buy.push_back(numeric_limits<double>::quiet_NaN());
            if(flag!=0){
                Sell.push_back(prices[i]);
                flag = 0;
            }
            else{
                Sell.push_back(numeric_limits<double>::quiet_NaN());
            }
        }
        else{
            Buy.push_back(numeric_limits<double>::quiet_NaN());
            Sell.push_back(numeric_limits<double>::quiet_NaN());
        }
    }
}
