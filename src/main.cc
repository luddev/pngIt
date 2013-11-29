#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>

#include "pngIt.h"

int main(int argc, char **argv)
{
 //Enter 
    pngIt png(argv[1],argv[2]);

    if(!png.verifyIsPNG())  {
        std::cout<<"Signature Mismatch, File is unlikely to be a PNG file."<<std::endl;
        exit(-1);
    }
    png.readChunks();
    std::cout<<"[!] Procceding to Encryption stage."<<std::endl;

	//Code Above seems to be working fine :)

    return 0;
}
