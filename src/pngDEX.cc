/*		pngEncoder/Decoder
 *	Author : ludkiller
 *	Last updated : 11/20/2013 00:07
 *	brief : Add stuff here.
 *
 *		TODO : 
 *			=> Write base 64 Encoder/Decoder helper functions.
 *			=> Add a license.
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <memory>

#include "pngDEX.h"
#include "crc32.h"



pngFileFormat pngF;

bool isPng;

void usage(std::string &programName)
{
	std::cout<<"usage : "
		 <<std::endl
		 <<programName<<" -e InputFile.txt InputFile.png OutputFile.png"
		 <<std::endl
		 <<programName<<" -d InputFile.png OutputFile.png"
		 <<std::endl;
}

chunk * loadChunk(FILE *pngFile,long int &offset)
{
	//fread moves File Pointer so no need for doing fseek 
	chunk *cType;
	cType = new chunk;
	offset = ftell(pngFile);
	unsigned char temp[4];
	memset(temp,0,4);
	memset(cType,0,sizeof(cType));
	fread(temp,4,1,pngFile);
	cType->length = (temp[0]<<24) | (temp[1]<<16) | (temp[2]<<8) | temp[3];
	std::cout<<"Chunk Length : "<<cType->length<<std::endl;
	//below line is reading more than 4 bytes some times 
	//need to fix this.
	std::size_t bytesread;
	bytesread = fread((void *)cType->chunkName,4,1,pngFile);

	if( bytesread != 4)	{
		std::cout<<"Reading Unspecified Amount of Data , Bytesread = "<<bytesread<<std::endl;
	}
	std::cout<<"Chunk Name : "<<cType->chunkName<<std::endl;
	cType->chunkData = new unsigned char[cType->length];


	if(cType->chunkData == NULL)	{
		std::cout<<"Unable to allocate data. "<<std::endl;
		return NULL;
	}
	fread(cType->chunkData,cType->length,1,pngFile);
	std::cout<<"Chunk Data : "<<cType->chunkData<<std::endl;
	memset(temp,0,4);
	fread(temp,4,1,pngFile);
	cType->CRC = (temp[0]<<24) | (temp[1]<<16) | (temp[2]<<8) | temp[3];
	std::cout<<"CRC : "<<cType->CRC<<std::endl;


	std::cout<<"FTELL = "<<ftell(pngFile)<<std::endl<<std::endl;
	std::string pattern = (const char *)cType->chunkName;
	
	if(strstr(pattern.c_str(),"IDAT"))	{
		

		std::cout<<"Pattern Matched, Found IDAT chunk at offset = "<<offset<<std::endl;
		return cType;
	}
	
	delete[] cType->chunkData;
	delete cType;

	return NULL;


}

void loadChunk(chunk *cType, FILE *pngFile)
{
	//fread moves File Pointer so no need for doing fseek 

	unsigned char temp[4];
	memset(temp,0,4);
	fread(&temp,4,1,pngFile);
	cType->length = (temp[0]<<24) | (temp[1]<<16) | (temp[2]<<8) | temp[3];
	std::cout<<"Chunk Length : "<<cType->length<<std::endl;
	fread(&cType->chunkName,1,4,pngFile);
	std::cout<<"Chunk Name : "<<cType->chunkName<<std::endl;
	cType->chunkData = new unsigned char[cType->length];
	fread(&cType->chunkData,1,cType->length,pngFile);
	fread(&cType->CRC,4,1,pngFile);
	std::cout<<"FTELL = "<<ftell(pngFile)<<std::endl<<std::endl;

}

void openPng(char *infileName,char *outfileName)
{
	isPng = true;
	FILE *inpngFile;
	inpngFile = fopen(infileName,"rb");
	FILE *opngFile;
	opngFile = fopen(outfileName,"wb");
	if(inpngFile == NULL)	{
		std::cout<<"Unable to open File "<< infileName <<std::endl;
		return;
	}
	fseek(inpngFile,0,SEEK_SET);
	fread(&pngF.signature,8,1,inpngFile);
	std::cout<<"File Pointer at = "<< ftell(inpngFile)<<std::endl;
	std::cout<<"Signature = "
	<<std::hex<<std::setiosflags (std::ios::showbase)<<std::setw(2)
	<<" "<<(int)pngF.signature[0]
	<<" "<<(int)pngF.signature[1]
	<<" "<<(int)pngF.signature[2]
	<<" "<<(int)pngF.signature[3]
	<<" "<<(int)pngF.signature[4]
	<<" "<<(int)pngF.signature[5]
	<<" "<<(int)pngF.signature[6]
	<<" "<<(int)pngF.signature[7]
	<<std::endl;
	isPng = false;

	unsigned char signature[] = {
		0x89,
		0x50,	//P = 0x50
		0x4E,	//N = 0x4E
		0x47,	//G	= 0x47
		0x0D,
		0x0A,
		0x1A,
		0x0A };
	
	if(pngF.signature[0] == 0x89)
		if(pngF.signature[1] == 0x50)
			if(pngF.signature[2] == 0x4E)
				if(pngF.signature[3] == 0x47)
					if(pngF.signature[4] == 0x0D)
						if(pngF.signature[5] == 0x0A)
							if(pngF.signature[6] == 0x1A)
								if(pngF.signature[7] == 0x0A)
									isPng = true;
	int i;
	i = 0;

	while(i<8)	{
		if(pngF.signature[i] != signature[i])
			isPng = false;

		i++;
	}
	if(!isPng)
		return;
	std::cout<<"Signature Matches as that of a PNG file."<<std::endl;

	/*
	loadChunk(&pngF.IHDR,pngFile);
	loadChunk(&pngF.PLTE,pngFile);
	loadChunk(&pngF.IDAT,pngFile);
	loadChunk(&pngF.IEND,pngFile);
	*/
	//Write a Pattern Finder, which loads a chunk one by one and 
	//searches for a pattern 
	chunk *tempchunk = NULL;
	long int offset = 0;
	while(!tempchunk)	{
		tempchunk = loadChunk(inpngFile,offset);
		if(feof(inpngFile))	{
			std::cout<<"End Of File Reached !"<<std::endl;
			exit(-9);
		}
	}

	//Place below code in other functions , this function should return the pixel Data 
	//Write up functions to edit pixel data and replace them in the png File.

	unsigned char *pixelData = tempchunk->chunkData;
	unsigned long pixelDataSize = tempchunk->length;
	std::cout<<std::endl;
	/*
	while(i != pixelDataSize)	{
		std::cout<<" "<<(int)pixelData[i];
		i++;
		if(i%10 == 0)
			std::cout<<std::endl;
	}
	*/
	std::cout<<std::endl;

		//	Write up a Bit Manupilation function
		//	and write back a new image file with changed pixel Data.
		//
		

		//Fix below code.
		int tempPixel = 0;
		char *text = "ABCDEFGHIJKLMNOPQRSTUWXYZ1234567890!@#$^&*()_+";
		std::cout<<"Length of pixel Data = "<<strlen((const char *)pixelData)<<std::endl;
		i = 0;
		while(i != pixelDataSize)	{
			tempPixel = text[i % 40];
			pixelData[i] |= tempPixel;
			i++;
		}
		i = 0;
		std::cout<<std::endl;
		/*
		while(i != pixelDataSize)	{
		std::cout<<" "<<(int)pixelData[i];
		i++;
		if(i%10 == 0)
			std::cout<<std::endl;
		}
		*/
		//Copy PNG and Make a new file 
		//Copy Modified Data in the IDAT chunk
		// Wolaa we have modified a png with a new one.
		copyPng(inpngFile,opngFile);
		fseek(opngFile,0,SEEK_SET);
		fseek(opngFile,offset + 8,SEEK_SET);
		std::cout<<std::endl<<std::endl<<std::endl;

		std::cout<<"File Pointer At Offset = "<<ftell(opngFile)<<std::endl;
		std::cout<<"Over Writiing ofsset = "<<offset + 8<<" to offset = "<<offset + 8 + pixelDataSize<<std::endl;
		fwrite((void *)pixelData,pixelDataSize,1,opngFile);


}

void pngEncrypt(char *plainText)
{

}

void copyPng(FILE *inpngFile, FILE *opngFile)
{
	char *buffer;
	long int sizepng;
	std::cout<<std::endl;
	std::cout<<"Initiating File Copy ...."<<std::endl;
	fseek(inpngFile,0,SEEK_SET);
	fseek(opngFile,0,SEEK_SET);

	fseek(inpngFile,0,SEEK_END);
	sizepng = ftell(inpngFile);

	buffer = new char[sizepng];

	fseek(inpngFile,0,SEEK_SET);
	fread(buffer,sizepng,1,inpngFile);

	fwrite(buffer,sizepng,1,opngFile);
	std::cout<<"File Copy Complete ...."<<std::endl;

}

int main(int argc, char **argv)	
{
	
	int param_no_t = 0;
	

	std::string programName = argv[0];

	if(argc == 1)	{
		usage(programName);
		exit(1);
	}
	std::string procedure = argv[1];

	if(procedure == "-d")
		param_no_t = 4;
	else if(procedure == "-e")
		param_no_t = 5;
	else {
		std::cout<<"[*] Invalid Operation "<<std::endl;
		usage(programName);
		exit(-3);
	}
	if(argc < param_no_t)	{
		usage(programName);
		exit(-1);
	}
	
	char *plainText = argv[2];
	char *outputPng = argv[4];

	openPng(argv[3],outputPng);
	
	if(!isPng)	{
		std::cout<<argv[3]<<" Is not a PNG File."<<std::endl;
		exit(-2);
	}
	std::cout<<"[!] PNG File Copied and Modified"<<std::endl;



}