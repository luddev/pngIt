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

    while ((c = getopt(argc, argv, "m:ed:o:i:")) != -1)
	switch (c) {
	case 'd':
	    dflag = 1;
	    dvalue = optarg;
	    break;
	case 'e':
	    eflag = 1;
	    //evalue = optarg;
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
	    abort();
	}

    //Get Arguments from user.
    //Now need to process them
    if(!iflag)	{
    	//print usage
    	fprintf(stderr, "Refer Manual page for pngIt\n");
    	return 1;
    }
    fprintf(stdout, "tada ...\n" );
    if(eflag & iflag & mflag)	{
    	fprintf(stdout, "Encrypting Data : \"%s\" Input File %s\n",mvalue, ivalue);

    	if (pngIt_Init(ivalue,ovalue) != PNG_INIT) {
    		fprintf(stderr, "Error Init\n" );
			return PNG_INIT_ERROR;
    	}
    }

    pngIt_dispose();

    return 0;
}
