#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "pngIt.h"

pngIt::pngIt()
{
    memset(&tempChunk,0,sizeof(tempChunk));
}

pngIt::pngIt(char *inFile, char *outFile)
{
    pngInFile = fopen(inFile,"rb");
    pngOutFile = fopen(outFile,"wb");
    offset = 0;
    currentFP = 0;
    plainText = NULL;
    memset(&tempChunk,0,sizeof(tempChunk));

}

pngIt::pngIt(char *inFile, char *outFile, char *_plainText)
{
    pngInFile = fopen(inFile,"rb");
    pngOutFile = fopen(outFile,"wb");
    offset = 0;
    currentFP = 0;
    plainText = _plainText;
    memset(&tempChunk,0,sizeof(tempChunk));
}

bool pngIt::verifyIsPNG()
{
    if(pngInFile == NULL)
        return false;

    fseek(pngInFile,0,SEEK_SET);
    fread(signature,1,8,pngInFile);
    unsigned char _signature[] = {
        0x89,
        0x50,   //P = 0x50
        0x4E,   //N = 0x4E
        0x47,   //G = 0x47
        0x0D,
        0x0A,
        0x1A,
        0x0A };

    int i = 0;
    std::cout<<"[*] Verifying Signature."<<std::endl;

    while(i<8)  {
        if(signature[i] != _signature[i])
            return false;
        i++;
    }

    std::cout<<"[*] Signature Verification Complete."<<std::endl;
    return true;

}

bool pngIt::readChunks()
{
    char temp[4];
    std::string tempKey;
    tempKey.clear();
    while(1) {
        if(feof(pngInFile)) {
            std::cout<<"[*] End of File reached."<<std::endl;
            return true;
        }
        memset(&tempChunk,0,sizeof(tempChunk));
        fread((void *)temp,1,4,pngInFile);
        tempChunk.length = (temp[0]<<24) | (temp[1]<<16) | (temp[2]<<8) | temp[3];
        fread((void *)tempChunk.chunkName,1,4,pngInFile);
        tempChunk.chunkData = new unsigned char[tempChunk.length];
        fread((void *)tempChunk.chunkData,1,tempChunk.length,pngInFile);
        fread((void *)temp,1,4,pngInFile);
        tempChunk.CRC = (temp[0]<<24) | (temp[1]<<16) | (temp[2]<<8) | temp[3];
        tempKey = (const char *)tempChunk.chunkName;
        chunkList.push_back(tempChunk);
        
        std::cout<<"Stored Chunk with Key = "<<tempKey.c_str()<<std::endl;
        delete[] tempChunk.chunkData;
        tempKey.clear();
    }

    return true;

}