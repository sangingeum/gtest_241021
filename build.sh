#!/bin/sh
g++ $1 -std=c++14 -O2 -I ./googletest/googletest/include/ -pthread -lgtest -L. -DGTEST_LEAK_TEST
