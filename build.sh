#!/bin/sh
# -fsanitize=address
g++ $1 -std=c++14 -O2 \
-I ./googletest/googletest/include/ \
-I ./googletest/googlemock/include/ \
-pthread -lgtest -L.
