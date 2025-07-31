#include <vector>
#include <algorithm>
#include <string>
    
    using namespace std;
    
    vector<double> fibonacci_levels(const vector<double>& prices) {
        if (prices.empty()) return {};
    
        double high = *max_element(prices.begin(), prices.end());
        double low  = *min_element(prices.begin(), prices.end());
    
        vector<double> levels = {0.0, 0.236, 0.382, 0.5, 0.618, 0.786, 1.0};
        vector<double> retracements;
    
        for (double level : levels) {
            double value = high - (high - low) * level;
            retracements.push_back(value);
        }
    
        return retracements;
    }
    
    string get_signal(double price, const vector<double>& levels) {
    
        double level_618 = levels[4];
        double level_382 = levels[2];
    
        if (price > level_618) return "BUY";
        else if (price < level_382) return "SELL";
        else return "HOLD";
    }