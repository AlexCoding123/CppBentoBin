#include <cstdint>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <cerrno>

inline void handle_error(const std::string& msg){
    throw std::runtime_error(msg + ": " + std::strerror(errno));
}

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
    try{
        if( argc != 3){
            std::cout << "Usage : mmap_create <file-name> <Message>" << std::endl;
        }

        size_t fsize;

        int fd = open(argv[1],  O_RDONLY);
        if(fd == -1){handle_error("open error");}

    }
    catch(const std::exception& e){
        std::cerr << "Fatal error" << e.what() << std::endl;
        return 1;
    }


    return 0;
}
