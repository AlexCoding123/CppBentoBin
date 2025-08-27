#include "ohlcv_1m.h"
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

int main(int argc, char* argv[]){
    try{
        if(argc < 3 || argc > 4){
            std::cerr << "Usage: " << argv[0] << " <file-name> <start-bar-index (1-based)> [num-bars]" << std::endl;
            return 1;
        }

        int          fd;
        char         *addr;
        off_t        offset, pa_offset;
        size_t       length;
        ssize_t      s;
        struct stat  sb;

        //Get the file descriptor from CL Argument
        fd = open(argv[1],  O_RDONLY);
        if(fd == -1){handle_error("open");}

        //fill sd with file stats
        if(fstat(fd, &sb) == -1){handle_error("fstat");}

        // Check that file size is divisible by sizeof(OhlcvBar)
        if (sb.st_size % sizeof(ohlcv_bar) != 0) {
            handle_error("file size is not a multiple of OhlcvBar; file may be corrupted or layout mismatched");
        }

        off_t barIndex = std::stoll(argv[2]) - 1; //One based indexing
        if(barIndex < 0) handle_error("Bar index must be bigger than 1");

        offset = barIndex * sizeof(ohlcv_bar);
        if (offset >= sb.st_size) {
            handle_error("offset");
        }

        size_t numBars;
        if(argc == 4){
            numBars = std::stoull(argv[3]);
        }else{
            numBars = (sb.st_size - offset) / sizeof(ohlcv_bar);
        }

        if(numBars == 0) handle_error("no bars to read");

        pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
        /* offset for mmap() must be page aligned */


        length = numBars * sizeof(ohlcv_bar);

        addr = static_cast<char*>(mmap(nullptr, length + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset));

        if(addr == MAP_FAILED) handle_error("mmap");

                // Access bars
        ohlcv_bar* bars = reinterpret_cast<ohlcv_bar*>(addr + (offset - pa_offset));
        for(size_t i = 0; i < numBars; ++i){
            std::cout << "Bar " << (barIndex + 1 + i)
                      << " ts: " << bars[i].ts_event
                      << ", open: " << bars[i].open
                      << ", high: " << bars[i].high
                      << ", low: " << bars[i].low
                      << ", close: " << bars[i].close
                      << ", volume: " << bars[i].volume
                      << std::endl;
        }

        // Cleanup
        munmap(addr, length + offset - pa_offset);
        close(fd);
    }
    catch(const std::exception& e){
        std::cerr << "Fatal error" << e.what() << std::endl;
        return 1;
    }


    return 0;
}
