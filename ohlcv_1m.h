#pragma once
#include <cstdint>

struct ohlcv_bar{
    uint64_t ts_event;      // ns timestamp
    int64_t open;           // 1e-9 price precision
    int64_t high;
    int64_t low;
    int64_t close;
    uint64_t volume;        // units traded
};

