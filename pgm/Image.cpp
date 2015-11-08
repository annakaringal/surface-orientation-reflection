/*
 -- Sample file --
 Source file "Image.C"
*/
#include <cstdio>
#include <cstdlib>
#include "Image.h"

Image::Image(){
    /* initialize image class */
    /* everything is zero...  */
    Ncols=0;
    Nrows=0;
    Ncolors=0;
    image=NULL;
}

Image::Image(const Image &im){
    /* initialize image class */
    /* Copy from im  */
  setSize(im.getNRows(), im.getNCols());
  setColors(im.getColors());
  int i,j;
  for (i=0; i<getNRows(); ++i)
    for (j=0; j<getNCols(); ++j){
      setPixel(i,j, im.getPixel(i,j));
    }
}


Image::~Image(){
    int i;
    if (image) {
	for (i=0; i<Nrows; i++)
	    free( image[i] );
	free(image);
    }
}
/*
 allocates space for an rows x columns image.

 returns : -2 if rows or columns <=0
           -1 if cannot allocate space
            rows * columns if success

*/

int
Image::setSize(int rows, int columns)
{
    int i;
    if (rows<=0 || columns <=0){
	printf("setSize: rows, columns must be positive\n");
	return -2;
    }

    if ( (image=(int **)malloc(sizeof (int *) * rows))==NULL ){
	printf("setSize: can't allocate space\n");
	return -1;
     }

    for (i=0; i<rows; i++) {
	if ( (image[i]=(int *)malloc(sizeof(int) * columns))==NULL){
	    printf("setSize: can't allocate space\n");
	    return -1;
	}
    }

    Nrows=rows;
    Ncols=columns;

    return rows*columns;
}


/*
 Sets the number of gray - levels
*/
int
Image::setColors(int colors){
  Ncolors=colors;
  return Ncolors;
}

/*
 Returns pixel i,j
 If image is "empty" return -1.
*/
int
Image::getPixel(int i, int j)const{
   if ( !image ) {
       printf("getPixel: read pixel from an empty image\n");
       return -1;
     }
  if (i<0 || i>Nrows || j<0 || j>Ncols){
//         error_msg("getPixel: out of image");
        return -1;
       }
       else
          return image[i][j];
}

/*
 set pixel i, j
 return -1 if error.
*/
int
 Image::setPixel(int i, int j, int color){
  if ( !image ) {
       printf("setPixel: write pixel to an empty image");
       return 0;
     }

 if ( i<0 || i>Nrows || j<0 || j>Ncols ){
 //  error_msg("Image::setPixel -> Out of boundaries\n");
   return -1;
 }
 image[i][j]=color;
 return color;
}





