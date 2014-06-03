#include "pngIt.h"


extern FILE *pngIt_src = NULL;
extern FILE *pngIt_dst = NULL;

extern png_structp pngIt_strucp_in = NULL;
extern png_infop pngIt_infop_in = NULL;
extern png_infop pngIt_endinfo = NULL;
extern png_unknown_chunk pngIt_unknown;


extern png_structp pngIt_strucp_out = NULL;
extern png_infop pngIt_infop_out = NULL;

extern int pngIt_height_max = 0;
extern int pngIt_width_max = 0;

const png_byte pngIt_chunk_name[5] = { 0x65 , 0x4e, 0x43, 0x78, (png_byte)'\0'};
                                        //e     N     C     x          \0


int pngIt_Init(char *infile, char *outfile = NULL)
{

    //Add something
    //open Source file.
    pngIt_src = fopen(infile,"rb");

    //Check if its a PNG ? 
    //if not close filehandle and 
    if(pngIt_src == NULL) {
      fprintf(stderr, "Error : %s does not exists.\n",infile );
    }
    if(pngIt_isPNG() != PNG_OK) {
      fprintf(stderr, "Error : %s is not a PNG file.\n", infile);
    }

    //Initialize pngIt_struct
    //Initialize pngIt_info
    pngIt_strucp_in = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
    if(pngIt_strucp_in == NULL) {
      fprintf(stderr, "Unable to Initialize png_structp\n");
      return PNG_INIT_ERROR;
    }
    pngIt_infop_in = png_create_info_struct(pngIt_strucp_in);

    if(pngIt_infop_in == NULL) {
      png_destroy_read_struct(&pngIt_strucp_in,(png_infopp)NULL,(png_infopp)NULL);
      fprintf(stderr, "Unable to Initialize png_infop\n");
      return PNG_INIT_ERROR;

    }

    pngIt_endinfo = png_create_info_struct(pngIt_strucp_in);

    if(pngIt_endinfo == NULL) {
      png_destroy_read_struct(&pngIt_strucp_in,&pngIt_infop_in,(png_infopp)NULL);
      fprintf(stderr, "Unable to Initialize png_infop end\n");
      return PNG_INIT_ERROR;
    }

    //Init libpng.

    png_init_io(pngIt_strucp_in,pngIt_src);
    
    fprintf(stdout, "Init png_structp\n");

    //tell libpng that we already checked signature of size SIGNATURE_SIZE = 8.
    png_set_sig_bytes(pngIt_strucp_in,SIGNATURE_SIZE);
    
    fprintf(stdout, "Set Signature Bytes Viewed\n");
    //set User call back for reading unknown chunks.
    //png_get_user_chunk_ptr(pngIt_strucp_in);
    
    png_set_read_user_chunk_fn(pngIt_strucp_in,(png_voidp)&pngIt_unknown,(png_user_chunk_ptr)pngIt_read_encoded_chunk_callback);
    fprintf(stdout, "Set Unknown Chunk Encounter Callback\n");

    char chunklist[5] = "eNCx";

    //Read Info

    //Either use 
    // png_read_info() - > png_read_image() -> png_read_end() 
    // OR use 
    // png_read_png()
    // use png_set_rows() to fetch rows.

    //png_bytep pngIt_row_pointers[pngIt_height_max];
    //Alloc Row Pointers.
    fprintf(stdout, "Setting up Memory for PNG Image.\n" );

    
    
    //Read PNG 
    png_read_png(pngIt_strucp_in, pngIt_infop_in, 0,NULL);

    //setup Bounds.
    pngIt_width_max = png_get_user_width_max(pngIt_strucp_in);
    pngIt_height_max = png_get_user_height_max(pngIt_strucp_in);

    pngIt_width_max = 1900;
    pngIt_height_max = 1600;

    png_set_user_limits(pngIt_strucp_in, pngIt_width_max, pngIt_height_max);

    /*
    unsigned char **row_pointers;
    row_pointers = (unsigned char **)malloc(pngIt_height_max);
    for(int i = 0 ; i < pngIt_height_max; i++)
      row_pointers[i] = (unsigned char *)malloc(pngIt_width_max);
    
    */

    fprintf(stdout, "Image : %dx%d \n",pngIt_width_max,pngIt_height_max );
    if(pngIt_width_max > 1900 && pngIt_height_max > 1600) {
      fprintf(stdout, "Weird Image Size : %dx%d \n",pngIt_width_max,pngIt_height_max );
      free(outfile);
      return PNG_INIT_ERROR;
    }

    png_bytep *row_pointers = (png_bytep *)png_malloc(pngIt_strucp_in, pngIt_height_max * sizeof(png_bytep));

    for (int i=0; i<pngIt_height_max;i++)
      row_pointers[i] = (png_bytep)png_malloc(pngIt_strucp_in, pngIt_width_max*1);


    fprintf(stdout, "Fetching Rows ...\n" );
    png_set_rows(pngIt_strucp_in, pngIt_infop_in, row_pointers);
    /*
    png_read_info(pngIt_strucp_in,pngIt_infop_in);

    png_read_image(pngIt_strucp_in, pngIt_row_pointers);
    
    //Read png End.
    png_read_end(pngIt_strucp_in, pngIt_endinfo);
    */

    char *tempfile;

    if(outfile == NULL) {
      tempfile = (char *)malloc(strlen(infile) + 10);
      sprintf(tempfile,"%s_enc.png",infile);
      fprintf(stdout, "Output File : %s\n",tempfile);
    }
    else  {
      fprintf(stdout, "Output File : %s\n",outfile);
    }
    //Open Destination file.
    pngIt_dst = fopen(tempfile,"wb");

    //Init Write File.

    //Copy Infile Contents to write file.

    //Update Write file with Encrypted blob ? 


    //Free all stuff.
    fprintf(stdout, "Deallocating Memory.\n");
    free(outfile);
    for (int i=0; i<pngIt_height_max; i++)
      free((void *)row_pointers[i]);
    free((void *)row_pointers);

    pngIt_strucp_out = png_create_write_struct(PNG_LIBPNG_VER_STRING,(png_voidp)NULL,NULL,NULL);
    if(pngIt_strucp_out == NULL)  {
      fprintf(stderr, "Unable to Allocate Write Struct.\n");
      return PNG_INIT_ERROR;
    }
    pngIt_infop_out = png_create_info_struct(pngIt_strucp_out);

    if(pngIt_infop_out == NULL) {
      png_destroy_write_struct(&pngIt_strucp_out,(png_infopp)NULL);
      return PNG_INIT_ERROR;
    }

    //Setup out pngIt_struct_out and feed it to libpng.
    png_init_io(pngIt_strucp_out,pngIt_dst);



    return PNG_INIT;

}

char *pngIt_encode(char *src)
{

    char *encMsg;


    return encMsg;
}

char *pngIt_decode(char *enc)
{
    char *dst;

    return dst;

}

int pngIt_dispose()
{
    png_destroy_read_struct(&pngIt_strucp_in,(png_infopp)NULL,(png_infopp)NULL);
    png_destroy_read_struct(&pngIt_strucp_in,&pngIt_infop_in,(png_infopp)NULL);
    fclose(pngIt_src);
    fclose(pngIt_dst);

    return PNG_DISPOSED;
}

int pngIt_isPNG()
{
    char header[SIGNATURE_SIZE];

    fread(header,1,SIGNATURE_SIZE,pngIt_src);

    if(png_sig_cmp((png_const_bytep)header,0,SIGNATURE_SIZE)) {

      return PNG_ERROR;
    }

    return PNG_OK;
}

int pngIt_copy()
{

    return 1;
}


int pngIt_read_encoded_chunk_callback(png_structp pngptr,png_unknown_chunkp chunk)
{
  //png_byte enc_chunk[5] = "eNCx";
  //png_byte *data;
  //png_size_t size;

  if(chunk->name[0] == pngIt_chunk_name[0] && chunk->name[1] == pngIt_chunk_name[1]
    && chunk->name[2] == pngIt_chunk_name[2] && chunk->name[3] == pngIt_chunk_name[3]
    && chunk->name[4] == pngIt_chunk_name[4]) 
  {
    //Found eNCx ? now do what you want.

  }

  //Add Code to process our encrypted blob.
  //if it exists.
  //Decode if Encrypted blob found.
  fprintf(stdout, "Callback called ! \n");

  //error im chunk.
  return -1;
  //unknown chunk.
  return 0;
  //success.
  return 1;


}
