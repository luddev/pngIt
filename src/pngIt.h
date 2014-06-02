#ifndef _PNG_IT_H
#define _PNG_IT_H

#include "common.h"

extern "C" {


    extern FILE *pngIt_src;
    extern FILE *pngIt_dst;

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

    int pngIt_Init();

/*
	pngIt_Init() 
	Usage : Initialize pngIt.
 */

    int pngIt_dispose();

    char *pngIt_encode(char *src);

    char *pngIt_decode(char *enc);

    int pngIt_isPNG();

    int pngIt_copy();

}
#endif				// _PNG_IT_H
