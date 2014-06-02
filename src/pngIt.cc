#include "pngIt.h"

extern "C" {

    int pngIt_Init() {

	//Add something

	return PNG_INIT;

    } char *pngIt_encode(char *src) {

	char *encMsg;


	return encMsg;
    }

    char *pngIt_decode(char *enc) {
	char *dst;

	return dst;

    }

    int pngIt_dispose() {

	return PNG_DISPOSED;
    }

    int pngIt_isPNG() {

	return PNG_OK;
    }

    int pngIt_copy() {

	return 1;
    }


}
