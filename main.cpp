#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>

struct OhlcvBar {
    uint64_t ts_event;      // Inclusive start time of the bar (ns since UNIX epoch)
    uint8_t  rtype;         // Record type: 32=OHLCV-1s, 33=OHLCV-1m, 34=OHLCV-1h, 35=OHLCV-1d
    uint16_t publisher_id;  // Publisher ID (dataset + venue)
    uint32_t instrument_id; // Instrument identifier

    int64_t open;           // Open price (1 unit = 1e-9)
    int64_t high;           // High price (1 unit = 1e-9)
    int64_t low;            // Low price  (1 unit = 1e-9)
    int64_t close;          // Close price (1 unit = 1e-9)

    uint64_t volume;        // Total traded volume during the bar
};


int main(int argc, char* argv[]){
    std::fstream fout;
    //std::string filename = argv[1];

    //unsigned short x = 8675;

    fout.open("bento-data.bin", std::ios::out | std::ios::binary);

    if(fout){
        fout.write(reinterpret_cast<char*>(&x), sizeof(unsigned short));
        fout.close();
    }else{
        std::cout << "error opening the file";
    }

    return 0;
}
