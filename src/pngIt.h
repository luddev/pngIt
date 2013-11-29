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


#ifndef _PNG_IT_H
#define _PNG_IT_H

#include <vector>
#include <string>

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



class pngIt {
	private:
		FILE *pngInFile;	//PNG Input File.
		FILE *pngOutFile;	//PNG Output File. 
		char *plainText;
		unsigned char signature[8];
		long int offset;	//Current Offset of File Pointer.
		long int currentFP;	//Current Position of File Pointer.
		std::vector<chunk> chunkList;	//A Hash Map container for ChunkList, char * corresnponds to the name of Chunk.
		chunk tempChunk;

	public:
		pngIt();
		pngIt(char *inFile, char *outFile);
		pngIt(char *inFile, char *outFile, char *plainText);

		bool verifyIsPNG();
		bool readChunks();





};

//	Add function declaration here.




#endif // _PNG_IT_H