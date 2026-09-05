#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/cpp"
g++ -std=c++17 -O2 -Iinclude src/*.cpp -o regex_engine
echo "Built cpp/regex_engine"
