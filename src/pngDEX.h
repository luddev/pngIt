/*		pngEncoder/Decoder
 *	Author : ludkiller
 *	Last updated : 11/20/2013 00:07
 *	brief : Add stuff here.
 *
 *		TODO : 
 *			=> Write base 64 Encoder/Decoder helper functions.
 *			=> Add a license.
 *			=> Add Recognition of more chunks.
 */


#ifndef _PNG_ENCIPHER_H
#define _PNG_ENCIPHER_H

/*
 *	Source: http://en.wikipedia.org/wiki/Portable_Network_Graphics
 *	PNG Signature : 0x89 0x50 0x4E 0x47 0x0D 0x0A 0x1A 0x0A
 *	PNG file is made up of chunks
 *	Chunk Format:
 *	Length 		Chunk Type		Chunk Data 		CRC
 *	4 Bytes 	4 Bytes			Length Bytes 	4 Bytes
 *	
 *	IHDR : Must be the first chunk, It contains the image width, height and depth.
 *	PLTE : Contains the pallete; list of colors.
 *	IDAT : Contains actual image data.
 *	IEND : Marks the image end.
 */

struct chunk	{
	unsigned long length;
	unsigned char chunkName[4];
	unsigned char *chunkData;
	unsigned long CRC;
};

struct pngFileFormat	{
	unsigned char signature[8];
	chunk IHDR;
	chunk PLTE;
	chunk IDAT; 
	chunk IEND;

};

void openPng(char *infileName,char *outfileName);

void pngEncrypt(char *plainText);

void pngDecrypt();

void usage(std::string &programName);

void loadChunk(chunk *cType, FILE *pngFile);

chunk * loadChunk(FILE *pngFile, long int &offset);

void copyPng(FILE *inpngFile, FILE *opngFile);

#endif // _PNG_ENCIPHER_H