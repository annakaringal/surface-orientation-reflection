/* Copyright: Anton Nikolaev, 1995 */
/* NO WARRANTIES: use at your own risk */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Image.h"



int readImage(Image *im, const char *fname)
/*
  reads image from fname;

  returns 0 if OK or -1 if something goes wrong.
*/
{
  FILE *input;
  char line[1024];
  int nCols,nRows;
  int levels;
  int i, j;

  /* open it */
  if (!fname || (input=fopen(fname,"r"))==0){
    printf("readImage: Cannot open file\n");
    return-1;
  }

  /* check for the right "magic number" */
  if (
        fread(line,1,3,input)!=3
      ||strncmp(line,"P5\n",3)
     )
  {
    fclose(input);
    printf("readImage: Expected .pgm file\n");
    return -1;
  }

  /* skip the comments */
  do
    fgets(line,sizeof line,input);
  while(*line=='#');

  /* read the width and height */
  sscanf(line,"%d %d\n",&nCols,&nRows);
  im->setSize( nRows, nCols);

  /* read # of gray levels */
  fgets(line,sizeof line,input);
  sscanf(line,"%d\n",&levels);
  im->setColors(levels);

  /* read pixel row by row */
  for(i=0;i<nRows;i++)
  {
    for(j=0;j<nCols;j++)
    {
      int byte=fgetc(input);

      if (byte==EOF) /* short file */
      {
        fclose(input);
        printf("readImage: short file\n");
        return -1;
      }
      else
        im->setPixel(i,j,byte);
    }
  }

  /* close the file */
  fclose(input);
  return 0; /* OK */
}

int writeImage(const Image *im, const char *fname)
/*
  writes the image into fname;

  returns 0 if OK or -1 if something goes wrong.
*/
{
  FILE *output;
  int nRows;
  int nCols;
  int colors;
  int i, j;

  /* open the file */
  if (!fname || (output=fopen(fname,"w"))==0){
    printf("writeImage: cannot open file\n");
    return(-1);
  }
  nRows=im->getNRows();
  nCols=im->getNCols();
  colors=im->getColors();

  printf("Saving image of size %d %d\n", nRows, nCols);
  /* write the header */
  fprintf(output,"P5\n"); /* magic number */
  fprintf(output,"#\n");  /* empty comment */
  fprintf(output,"%d %d\n%03d\n",nCols,nRows,colors); /* image info */

  /* write pixels row by row */
  for(i=0;i<nRows;i++)
  {
    for(j=0;j<nCols;j++)
    {
      int byte=im->getPixel(i,j);

      if (fputc(byte,output)==EOF) /* couldn't write */
      {
	    fclose(output);
            printf("writeImage: could not write\n");
	    return -1;
      }
    }
  }

  /* close the file */
  fclose(output);
  return 0; /* OK */
}

