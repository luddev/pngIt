#ifndef _PNG_IT_H
#define _PNG_IT_H

#include "common.h"

#define SIGNATURE_SIZE 8

extern "C" {


    extern FILE *pngIt_src;
    extern FILE *pngIt_dst;

    extern png_structp pngIt_structp_in;
    extern png_infop pngIt_infop_in;
    extern png_infop pngIt_endinfo;

    extern png_unknown_chunk pngIt_unknown;

    extern png_structp pngIt_structp_out;
    extern png_infop pngIt_infop_out

    extern int pngIt_height_max;
    extern int pngIt_width_max;



    enum PNGIT {
	PNG_INIT,
	PNG_INIT_ERROR,
	PNG_OK,
	PNG_ERROR,
	PNG_DECODE_ERROR,
	PNG_DECODED,
	PNG_ENCODE_ERROR,
	PNG_ENCODED,
	PNG_DISPOSED,
	PNG_DISPOSE_ERROR
    };

/*
 *	pngIt_Init() 
 *	Usage : Initialize pngIt. 
 */

    int pngIt_Init(char *infile, char *outfile);

/*
	pngIt_Init() 
	Usage : Initialize pngIt.
 */

    int pngIt_dispose();

    char *pngIt_encode(char *src);

    char *pngIt_decode(char *enc);

    int pngIt_isPNG();

    int pngIt_copy();


    //libpng callbacks.

    int pngIt_read_encoded_chunk_callback(png_structp pngptr,png_unknown_chunkp chunk);
    int pngIt_write_encoded_chunk_callback(png_structp pngptr,png_unknown_chunkp chunk);

}
#endif				// _PNG_IT_H
