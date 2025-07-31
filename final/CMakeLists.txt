cmake_minimum_required(VERSION 3.14)
project(SOCTradingStrategies)

set(CMAKE_CXX_STANDARD 17)

# This assumes pybind11 is installed via pip
# You can find where pip installed it by running:
# python -m pybind11 --cmakedir
execute_process(
  COMMAND python3 -m pybind11 --cmakedir
  OUTPUT_VARIABLE pybind11_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

list(APPEND CMAKE_PREFIX_PATH ${pybind11_dir})
find_package(pybind11 REQUIRED)

pybind11_add_module(trading_bindings
    bindings.cpp
    Fibonacci.cpp
    BollingerBands.cpp
    MACD.cpp
)
