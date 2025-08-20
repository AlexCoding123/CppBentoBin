#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[]){
    std::fstream fout;
    std::string filename = argv[1];

    fout.open("bento-data.bin", std::ios::out | std::ios::binary);

    if(fout){
        fout.write();
    }

    return 0;
}
