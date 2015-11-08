/* Copyright: Anton Nikolaev, 1995 */
/* NO WARRANTIES: use at your own risk */

/* macro to swap 2 variables bit by bit */
#ifdef SWAP
#undef SWAP
#endif
#define SWAP(a,b) {a^=b; b^=a; a^=b;}

#include "Image.h"

enum /* scan direction */
{
  DIR_X,
  DIR_Y
};


int line(Image *&im, int x0, int y0, int x1, int y1, int color)
/*  
  draws a line of given gray-level color from (x0,y0) to (x1,y1);
  im is the pointer to the user defined image structure - 
  whatever it is;

  returns 0;    

  uses the function setPixel(struct image *im, int x, int y, int color)
  to actually set pixels in the image to the given color; 

  IMPORTANT: (x0,y0) and (x1,y1) can lie outside the image 
  boundaries, so setPixel() should check the coordinates passed to it;

  implements the Bresenham's incremental midpoint algorithm;
  (adapted from J.D.Foley, A. van Dam, S.K.Feiner, J.F.Hughes
  "Computer Graphics. Principles and practice", 
  2nd ed., 1990, section 3.2.2);  
*/
{  
  int xmin,xmax; /* line coordinates */
  int ymin,ymax;
  int dir;       /* scan direction */
  int dx;        /* distance along X */
  int dy;        /* distance along Y */

  /* increments: East, North-East, South, South-East, North */
  int incrE,
      incrNE,
      incrS,
      incrSE,
      incrN;     
  int d;         /* the D */
  int x,y;       /* running coordinates */
  int mpCase;    /* midpoint algorithm's case */
  int done;      /* set to 1 when done */

  xmin=x0;
  xmax=x1;
  ymin=y0;
  ymax=y1;
  
  dx=xmax-xmin;
  dy=ymax-ymin;

  if (dx*dx>dy*dy) /* horizontal scan */
  {
    dir=DIR_X;
    if (xmax<xmin)
    {
      SWAP(xmin,xmax);
      SWAP(ymin,ymax);
    }
    dx=xmax-xmin;
    dy=ymax-ymin;

    if (dy>=0)
    {
      mpCase=1;
      d=2*dy-dx;      
    }
    else
    {
      mpCase=2;
      d=2*dy+dx;      
    }

    incrNE=2*(dy-dx);
    incrE=2*dy;
    incrSE=2*(dy+dx);
  }
  else /* vertical scan */
  {
    dir=DIR_Y;
    if (ymax<ymin)
    {
      SWAP(xmin,xmax);
      SWAP(ymin,ymax);
    }
    dx=xmax-xmin;
    dy=ymax-ymin;    

    if (dx>=0)
    {
      mpCase=1;
      d=2*dx-dy;      
    }
    else
    {
      mpCase=2;
      d=2*dx+dy;      
    }

    incrNE=2*(dx-dy);
    incrE=2*dx;
    incrSE=2*(dx+dy);
  }
  
  /* start the scan */
  x=xmin;
  y=ymin;
  done=0;

  while(!done)
  {
    im->setPixel(x,y,color);
  
    /* move to the next point */
    switch(dir)
    {
      case DIR_X: /* horizontal */
      {
        if (x<xmax)
        {
	      switch(mpCase)
          {
            case 1:
	          if (d<=0)
	          {
	            d+=incrE;  x++;
	          }
              else
              {
                d+=incrNE; x++; y++;
              }
            break;
  
            case 2:
              if (d<=0)
              {
                d+=incrSE; x++; y--;
              }
              else
              {
                d+=incrE;  x++;
              }
            break;
	      } /* mpCase */
        } /* x<xmax */
        else
	      done=1;
      }  
      break;

      case DIR_Y: /* vertical */
      {
        if (y<ymax)
        {
          switch(mpCase)
          {
            case 1:
              if (d<=0)
              {
                d+=incrE;  y++;
              }
              else
              {
                d+=incrNE; y++; x++;
              }
            break;
  
            case 2:
              if (d<=0)
              {
                d+=incrSE; y++; x--;
              }
              else
              {
                d+=incrE;  y++;
              }
            break;
	      } /* mpCase */
        } /* y<ymin */
        else
	      done=1;
      }
      break;    
    }
  }

  return 0; /* no error */
}




