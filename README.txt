Anna Karingal
November 15, 2015
Computer Vision
Homework 4

FORMULA FOR CALCULATING NORMAL OF LIGHT SOURCE
---------------------------------------------------------
z - z0 = sqrt((x-x0)^2 + (y-y0)^2 + r^2)


FORMULA FOR CALCULATING NORMAL OF OBJECT AT PIXEL I,J
---------------------------------------------------------
I = vector of values of intensites of pixel i,j for each img (3x1)
L = light source orientation vectors for each light source (3x3)
a = albedo at pixel i,j
N = object normal at pixel i,j

aN = inverse(L) * I
a = |N|
N = aN / |N|

FORMULA FOR CALCULATING MATRIX INVERSE
---------------------------------------------------------
inverse = (1/determinant) * adjugate of matrix

STEP & THRESHOLD FOR OUTPUT IMAGES ---------------------------------------------------------
s3: step      -- 10
    threshold -- 85

s4: threshold -- 85