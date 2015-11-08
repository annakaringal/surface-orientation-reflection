/*
 -- Sample file --
  Header file "Image.h"
*/


/*
  Definition of "struct image"
*/

#ifndef _IMAGE
#define _IMAGE

class Image{
 private:
  int Nrows; /*number of rows */
  int Ncols; /*number of columns */
  int Ncolors; /*number of gray level colors */
  int **image;

 public:
  Image();
  Image (const Image &im);
  ~Image();

/*
 Functions applied to "struct image"
*/

/*
   sets the size of the image to the given
    height (# of rows) and width (# of columns);
    returns 0 if OK or -1 if fails;
*/
int setSize(int rows, int columns);


/*
  returns the number of columns in the image;
*/
int getNCols()const{return Ncols;};
/*
returns the number of rows in the image;
*/
int getNRows()const{return Nrows;};
/*
  sets the number of gray-level colors in the image
    (not counting 0);
    returns 0 if OK or -1 if fails;
*/
 int setColors(int colors);
/*
  returns the number of gray-level colors in the image;
*/
 int getColors()const{ return Ncolors; };
/*
  sets the pixel in the image at row i and column j
  to a particular color;
*/
 int setPixel( int i, int j, int color );
/*
  returns the color of the pixel in the image at row i and column j;
*/
 int getPixel( int i, int j )const;

};


/*
 functions for read-write pgm images
*/

int
readImage(Image *im, const char *filename);
int
writeImage(const Image *im, const char *filename);

/*
function for drawing a line
*/

int
line(Image *&im, int x0, int y0, int x1, int y1, int color);

#endif
