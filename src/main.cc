/*				pngIt
 *	Author : ludkiller
 *	Last updated : 11/29/2013 21:19
 *	brief : Add stuff here.
 *
 *		TODO : 
 *			=> Write base 64 Encoder/Decoder helper functions.	//DONE
 *			=> Add a license.
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>

#include "pngIt.h"
#include "base64.h"

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
	//So we got IDAT, write a function which can 
	//place the encrypted/encoded plainText into IDAT
	//such that IDAT is not affected.

	char *plainText = argv[3];
	std::string encodedText = base64_encode((const unsigned char *)plainText,strlen(plainText));
	std::cout<<plainText<<std::endl;
	std::cout<<encodedText<<std::endl;
	png.rebuildIDAT(encodedText.c_str());
    return 0;
}
