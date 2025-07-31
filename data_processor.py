import trading_bindings as tb
import pandas as pd

def generate_features(price_series):
    prices = price_series.tolist()

    macd = tb.calculate_macd(prices)
    bb = tb.calculate_bollinger_bands(prices, window=20, num_std=2)
    fib = tb.calculate_fibonacci_levels(prices)

    df = pd.DataFrame({
        "price": prices,
        "macd": [None]*(len(prices) - len(macd)) + macd,
        "bollinger_upper": [b[0] for b in bb],
        "bollinger_lower": [b[1] for b in bb],
        "fib_0": fib[0],
        "fib_23.6": fib[1],
        "fib_38.2": fib[2],
        "fib_61.8": fib[3],
        "fib_100": fib[4],
    })

    return df