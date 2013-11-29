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
#include <string>
#include <vector>

#include "pngIt.h"

pngIt::pngIt()
{
    offset = 0;
    currentFP = 0;
    plainText = NULL;
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
    unsigned char temp[4];
    int i=0;
    
    while(1) {
        if(feof(pngInFile)) {
            std::cout<<"[*] End of File reached."<<std::endl;
            return true;
        }
		std::cout<<std::endl<<std::endl;
		offset = ftell(pngInFile);
		std::cout<<std::hex<<std::showbase<<"PNG File Current Offset "<<offset<<std::endl<<std::endl;
		memset(&temp,0,4);
        memset(&tempChunk,0,sizeof(tempChunk));
        fread((void *)temp,1,4,pngInFile);
        tempChunk.length = (temp[0]<<24) | (temp[1]<<16) | (temp[2]<<8) | temp[3];
		fread((void *)tempChunk.chunkName,4,1,pngInFile);
        tempChunk.chunkData = new unsigned char[tempChunk.length];
        fread((void *)tempChunk.chunkData,tempChunk.length,1,pngInFile);
		memset(&temp,0,sizeof(temp));
        fread((void *)temp,4,1,pngInFile);
        tempChunk.CRC = (temp[0]<<24) | (temp[1]<<16) | (temp[2]<<8) | temp[3];
        
		//Display Data
		std::cout<<"Stored Chunk with Key = ";
		for(i=0;i<4;i++)	{
			std::cout<<tempChunk.chunkName[i];
		}
		std::cout<<std::endl;
		std::cout<<"Lenght of chunkData = "<<tempChunk.length<<std::endl;
		std::cout<<"Stored Chunk with Data = ";
        chunkList.push_back(tempChunk);
        for(i=0;i<tempChunk.length;i++)	{
			std::cout<<std::hex<<std::showbase<<(int)tempChunk.chunkData[i]<<"\t";
		}
		std::cout<<std::endl;
        std::cout<<"CRC = "<<tempChunk.CRC<<std::endl;

		std::cout<<std::endl<<std::endl;
		delete[] tempChunk.chunkData;
		currentFP = ftell(pngInFile);

		//std::cout<<std::hex<<"PNG File Current FP "<<currentFP<<std::endl;

		if(tempChunk.chunkName[0] == 'I')
			if(tempChunk.chunkName[1] == 'E')
				if(tempChunk.chunkName[2] == 'N')
					if(tempChunk.chunkName[3] == 'D')
						return true;


    }

    return true;

}

bool pngIt::rebuildIDAT(const char *encodedText)
{
	//IDAT rebuilding code in here.
	//std::vector<chunk>::iterator i;
	
	int len = chunkList.size();
	int index;
	for(index = 0; index < len ; index++)	{
		if(chunkList[index].chunkName[0] == 'I')
			if(chunkList[index].chunkName[1] == 'D')
				if(chunkList[index].chunkName[2] == 'A')
					if(chunkList[index].chunkName[3] == 'T')
						break;
	}
	
	tempChunk = chunkList[index];
	int i = 0;
	for(i=0;i<4;i++)	{
		std::cout<<tempChunk.chunkName[i];
	}



	return true;
}