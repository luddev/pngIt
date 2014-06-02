/*				pngIt
 *	Author : ???
 *	Last updated : 11/20/2013 00:07
 *	brief : Add stuff here.
 *
 *		TODO : 
 *			=> Write base 64 Encoder/Decoder helper functions.	//DONE
 *			=> Add a license.
 */

#ifndef _BASE64_H_
#define _BASE64_H_

#include "common.h"

std::string base64_encode(unsigned char const *, unsigned int len);
std::string base64_decode(std::string const &s);
#endif
