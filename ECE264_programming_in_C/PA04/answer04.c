#include <stdint.h>
#include "answer04.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#define FALSE 0
#define TRUE 1

static int ECE_checkValid(ImageHeader * header);
static int ECE_checkComment(char * comment, int len) ; 
/**
 * Loads an ECE264 image file, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
Image * Image_load(const char * filename){
  FILE * fp = NULL;
  size_t read;
  ImageHeader header;
  Image * tmp_im = NULL, * im = NULL;
  size_t n_bytes = 0;
  int err = FALSE;

  if(!err) { // Open filename
    fp = fopen(filename, "rb");
    if(!fp) {
      fprintf(stderr, "Failed to open file '%s'\n", filename);
      err = TRUE;
    }
  }

  if(!err) { // Read the header
    read = fread(&header, sizeof(ImageHeader), 1, fp);
    printf("read = %zd\n", read); 
    if(read != 1) {
      fprintf(stderr, "Failed to read header from '%s'\n", filename);
      err = TRUE;
    }
  }

 if(!err) { // We're only interested in a subset of valid bmp files
    if(!ECE_checkValid(&header)) {
      fprintf(stderr, "Invalid header in '%s'\n", filename);
      err = TRUE;
    }
  }

  if(!err) { // Allocate Image struct
    tmp_im = malloc(sizeof(Image));
    if(tmp_im == NULL) {
      fprintf(stderr, "Failed to allocate im structure\n");
      err = TRUE;
    } 
  }

  if(!err) { // Init the Image struct
    tmp_im->width = header.width;
    tmp_im->height = header.height;
    
    // Handle the comment
    /* char * filename_cpy = strdup(filename);// we want to call basename */
    /* char * file_basename = basename(filename_cpy); // requires editable str */
    /* const char * prefix = "Original ECE file: "; */
    /* n_bytes = sizeof(char) * (strlen(prefix) + strlen(file_basename) + 1); */



    tmp_im->comment = malloc(sizeof(uint8_t)*header.comment_len);
    if(tmp_im->comment == NULL) {
      fprintf(stderr, "Failed to allocate %zd bytes for comment\n",
    	      n_bytes);
      err = TRUE;
    }
    /* } else { */
    /*   sprintf(tmp_im->comment, "%s%s", prefix, file_basename); */
    /* } */
    /* free(filename_cpy); // this also takes care of file_basename */

    

    // Handle image data
    n_bytes = sizeof(uint8_t) * header.width * header.height;
    tmp_im->data = malloc(n_bytes);
    if(tmp_im->data == NULL) {
      fprintf(stderr, "Failed to allocate %zd bytes for image data\n",
	      n_bytes);
      err = TRUE;
    }
  }

  /* if(!err) { // Seek the start of the pixel data */
  /*   if(fseek(fp, header.offset, SEEK_SET) != 0) { */
  /*     fprintf(stderr, "Failed to seek %d, the data of the image data\n", */
  /* 	      header.offset); */
  /*     err = TRUE; */
  /*   } */
  /* } */
  

  if(!err) { // Read pixel data
    //size_t bytes_per_row = ((header.bits * header.width + 31)/32) * 4;
    //size_t bytes_per_row = ((1 * header.width + 31)/32) * 4;
    //n_bytes = bytes_per_row * header.height;

    read = fread(tmp_im->comment, sizeof(uint8_t), header.comment_len, fp);

    if(read<header.comment_len) {
      fprintf(stderr, "Comment length is more than it can be read\n"); 
      err=TRUE; 
    }
  }

  if(!err) {
    if(!ECE_checkComment(tmp_im->comment, header.comment_len)) {
      fprintf(stderr, "No null byte in the comment section\n"); 
      err=TRUE; 
    }
  }

  if(!err) {
    size_t array_len = header.width*header.height;
    uint8_t * rawECE = malloc(array_len);
    if(rawECE == NULL) {
      fprintf(stderr, "Could not allocate %zd bytes of image data\n",
  	      array_len);
      err = TRUE;
    } else {
      read = fread(rawECE, sizeof(uint8_t), array_len, fp);
      if(array_len!= read) {
  	fprintf(stderr, "Only read %zd of %zd bytes of image data\n",
  		read, array_len);
  	err = TRUE;
      } else {
  	// Must convert RGB to grayscale
  	//uint8_t * write_ptr = tmp_im->data;
  	//uint8_t * read_ptr;
  	//int intensity;
	//read_ptr = &rawECE[0]; */
  	//int row, col; // row and column
  	/* for(row = 0; row < header.height; ++row) { */
  	/*   read_ptr = &rawbmp[row * bytes_per_row]; */
  	/*   for(col = 0; col < header.width; ++col) { */
  	/*     intensity  = *read_ptr++; // blue */
  	/*     intensity += *read_ptr++; // green */
  	/*     intensity += *read_ptr++; // red */
  	/*     *write_ptr++ = intensity / 3; // now grayscale */
  	/*   } */
  	/* } */
	int ind; 
	for(ind=0; ind<array_len; ind++) {
	  tmp_im->data[ind] = rawECE[ind];
	}


      }
    }
    free(rawECE);
  }

  if(!err) { // We should be at the end of the file now
    uint8_t byte;
    read = fread(&byte, sizeof(uint8_t), 1, fp);
    if(read != 0) {
      fprintf(stderr, "Stray bytes at the end of bmp file '%s'\n",
  	      filename);
      err = TRUE;
    }
  }

  if(!err) { // We're winners...
    im = tmp_im;  // bmp will be returned
    tmp_im = NULL; // and not cleaned up
  }

  // Cleanup


  if(tmp_im != NULL) {
    free(tmp_im->comment); // Remember, you can always free(NULL)
    free(tmp_im->data);
    free(tmp_im);
  }
  if(fp) {
    fclose(fp);
  }
  if(err) im=NULL; 
  return im;
}



/**
 * Save an image to the passed filename, in ECE264 format.
 * Return TRUE if this succeeds, or FALSE if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
int Image_save(const char * filename, Image * image) {
  int err = FALSE; 
  FILE * fp = NULL;
  uint8_t * buffer = NULL;    
  size_t written = 0;

  // Attempt to open file for writing
  fp = fopen(filename, "wb");
  if(fp == NULL) {
    fprintf(stderr, "Failed to open '%s' for writing\n", filename);
    return FALSE; // No file ==> out of here.
  }

  // Number of bytes stored on each row
  //  size_t bytes_per_row = ((24 * image->width + 31)/32) * 4;
  
  // Prepare the header
  ImageHeader header; 
  header.magic_number =  ECE264_IMAGE_MAGIC_NUMBER; 
  header.width = image->width; 
  header.height = image->height ; 
  header.comment_len =strlen(image->comment)+1; 
  size_t array_len = header.width * header.height; 
  if(!err) {  // Write the header
    written = fwrite(&header, sizeof(header), 1, fp);
    if(written != 1) {
      fprintf(stderr, 
	      "Error: only wrote %zd of %zd of file header to '%s'\n",
	      written, sizeof(header), filename);
      err = TRUE;
    }
  }


  // write comments
  fwrite(image->comment, sizeof(char), header.comment_len, fp); 


  if(!err) { // Before writing, we'll need a write buffer
    buffer = malloc(array_len);
    if(buffer == NULL) {
      fprintf(stderr, "Error: failed to allocate write buffer\n");
      err = TRUE;
    } else {
      // not strictly necessary, we output file will be tidier.
      memset(buffer, 0, array_len); 
    }
  }

  if(!err) { // Write pixels
    /* uint8_t * read_ptr = image->data; */
    /* int row, col; // row and column */
    /* for(row = 0; row < header.height && !err; ++row) { */
    /*   uint8_t * write_ptr = buffer; */
    /*   for(col = 0; col < header.width; ++col) { */
    /* 	*write_ptr++ = *read_ptr; // blue */
    /* 	*write_ptr++ = *read_ptr; // green */
    /* 	*write_ptr++ = *read_ptr; // red */
    /* 	read_ptr++; // advance to the next pixel */
    /*   } */
      // Write line to file
    
    
    
    written = fwrite(image->data, sizeof(uint8_t), array_len, fp);
    if(written != array_len) {
      fprintf(stderr, "Failed to write pixel data to file\n");
      err = TRUE;
      }
    }
  /* } */
    
  // Cleanup
  free(buffer);
  if(fp)
    fclose(fp);

  return !err;
}

/**
 * Free memory for an image structure
 *
 * Image_load(...) (above) allocates memory for an image structure. 
 * This function must clean up any allocated resources. If image is 
 * NULL, then it does nothing. (There should be no error message.) If 
 * you do not write this function correctly, then valgrind will 
 * report an error. 
 */

void Image_free(Image * image) {
  free(image->comment); 
  free(image->data); 
  free(image); 
}

/**
 * Performs linear normalization, see README
 */
void linearNormalization(int width, int height, uint8_t * intensity)  {
  int min = intensity[0];
  int max = intensity[0]; 
  int i; 
  int len = width*height;
  for(i=0;i<len; i++) {
    if(intensity[i]<min) min=intensity[i]; 
    if(intensity[i]>max) max=intensity[i]; 
  }
  
  int ind; 
  for(ind=0; ind<len; ind++) {
    intensity[ind]= (intensity[ind]-min)*255.0/(max-min); 
  }

}

static int ECE_checkValid(ImageHeader * header) {
  if(header->magic_number!=ECE264_IMAGE_MAGIC_NUMBER) return FALSE; 
  if(header->width==0 || header->height ==0) return FALSE; 
  return TRUE; 
}


static int ECE_checkComment(char * comment, int len) {
  int i=0; 
  int ret = FALSE; 
  for(i=0; i<len; i++) {
    if(comment[i]=='\0') ret=TRUE; 

  }




  return ret; 

}
