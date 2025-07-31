
import pandas as pd
import numpy as np
from cpp_bindings import get_macd_signals, get_rsi_signals, get_supertrend_signals
from data_processor import preprocess_features
from model import TradingNN
from train import train_model
from test import evaluate_model
import torch
import os


os.makedirs("results", exist_ok=True)
os.makedirs("models", exist_ok=True)


train_data = pd.read_csv("data/AAPL_training.csv", parse_dates=["Date"])
test_data = pd.read_csv("data/AAPL_testing.csv", parse_dates=["Date"])


train_data["MACD_signal"] = get_macd_signals(train_data["Close"].values.tolist())
train_data["RSI_signal"] = get_rsi_signals(train_data["Close"].values.tolist())
train_data["Supertrend_signal"] = get_supertrend_signals(train_data["Close"].values.tolist())

test_data["MACD_signal"] = get_macd_signals(test_data["Close"].values.tolist())
test_data["RSI_signal"] = get_rsi_signals(test_data["Close"].values.tolist())
test_data["Supertrend_signal"] = get_supertrend_signals(test_data["Close"].values.tolist())


X_train, y_train = preprocess_features(train_data)
X_test, y_test = preprocess_features(test_data)

model = TradingNN(input_size=X_train.shape[1])
criterion = torch.nn.BCELoss()  
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)


train_model(model, criterion, optimizer, X_train, y_train, epochs=20)
torch.save(model.state_dict(), "models/nn_model_weights.pth")


results = evaluate_model(model, X_test, y_test)


results_df = pd.DataFrame([results])
results_df.to_csv("results/strategy_performance.csv", index=False)

print(" Evaluation complete. Metrics saved to results/strategy_performance.csv")