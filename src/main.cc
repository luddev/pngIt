#include "common.h"
#include "pngIt.h"

int main(int argc, char **argv)
{

	int mflag = 0;
	int eflag = 0;
	int dflag = 0;
	int oflag = 0;
	int iflag = 0;
	char c;

	char *mvalue = NULL;
	char *evalue = NULL;
	char *dvalue = NULL;
	char *ovalue = NULL;
	char *ivalue = NULL;

	while ((c = getopt (argc, argv, "m:e:d:o:i:")) != -1)
         switch (c)
           {
           case 'd':
             dflag = 1;
             dvalue = optarg;
             break;
           case 'e':
             eflag = 1;
             evalue = optarg;
             break;
           case 'm':
             mflag = 1;
             mvalue = optarg;
             break;
           case 'i':
           	 iflag = 1;
           	 ivalue = optarg;
           	 break;
           case 'o':
           	 oflag = 1;
           	 ovalue = optarg;
           	 break;
           case '?':
             //pritn help? 
             return 1;
           default:
             abort ();
        	}

    //Get Arguments from user.
   	//Now need to process them

	if(pngIt_Init() != PNG_INIT)	{

		return PNG_INIT_ERROR;
	}



    return 0;
}
