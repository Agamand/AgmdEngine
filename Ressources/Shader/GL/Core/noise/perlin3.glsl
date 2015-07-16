
#ifndef _PERLIN3_GLSL_
#define _PERLIN3_GLSL_

#include "perlin.glsl"
#include "noise_table.glsl"
/*
	LIBnoise conversion c++ to glsl

*/


float Interpolate(float x0, float x1, float alpha)
{
   return x0 * (1 - alpha) + alpha * x1;
}


/*
float persistence = 0.5f, frequency = 0.2f, amplitude = 1.f,
lacunarity = 2.0f;
int octaves = 8, randomseed = 5465463;

float Total(float,float);
float GetValue(float,float);
float Noise(int,int);
float Interpolate(float,float,float);

float GetHeight(float x, float y, float p,float f,int o, int seed)
{
  //persistence = p;
  //frequency = f;
  //octaves = o;
  //randomseed = 2+seed*seed;
  return amplitude * Total(x, y);
}

float Total(float i, float j)
{
  //properties of one octave (changing each loop)




  float t = 0.0f;
  float _amplitude = 1;
  float freq = frequency;

  for(int k = 0; k < octaves; k++) 
  {
    t += GetValue(j * freq + randomseed, i * freq + randomseed) * _amplitude;
    _amplitude *= persistence;
    freq *= 2;
  }

  return t;
}

float GetValue(float x, float y)
{
  int Xint = int(x);
  int Yint = int(y);
  float Xfrac = x - Xint;
  float Yfrac = y - Yint;

  //noise values
  float n01 = Noise(Xint-1, Yint-1);
  float n02 = Noise(Xint+1, Yint-1);
  float n03 = Noise(Xint-1, Yint+1);
  float n04 = Noise(Xint+1, Yint+1);
  float n05 = Noise(Xint-1, Yint);
  float n06 = Noise(Xint+1, Yint);
  float n07 = Noise(Xint, Yint-1);
  float n08 = Noise(Xint, Yint+1);
  float n09 = Noise(Xint, Yint);

  float n12 = Noise(Xint+2, Yint-1);
  float n14 = Noise(Xint+2, Yint+1);
  float n16 = Noise(Xint+2, Yint);

  float n23 = Noise(Xint-1, Yint+2);
  float n24 = Noise(Xint+1, Yint+2);
  float n28 = Noise(Xint, Yint+2);

  float n34 = Noise(Xint+2, Yint+2);

  //find the noise values of the four corners
  float x0y0 = 0.0625*(n01+n02+n03+n04) + 0.125*(n05+n06+n07+n08) + 0.25*(n09);  
  float x1y0 = 0.0625*(n07+n12+n08+n14) + 0.125*(n09+n16+n02+n04) + 0.25*(n06);  
  float x0y1 = 0.0625*(n05+n06+n23+n24) + 0.125*(n03+n04+n09+n28) + 0.25*(n08);  
  float x1y1 = 0.0625*(n09+n16+n28+n34) + 0.125*(n08+n14+n06+n24) + 0.25*(n04);  

  //interpolate between those values according to the x and y fractions
  float v1 = Interpolate(x0y0, x1y0, Xfrac); //interpolate in x direction (y)
  float v2 = Interpolate(x0y1, x1y1, Xfrac); //interpolate in x direction (y+1)
  float fin = Interpolate(v1, v2, Yfrac);  //interpolate in y direction

  return fin;
}

float GetValue(float x, float y, float z)
{
  int Xint = int(x);
  int Yint = int(y);
  int Zint = int(z);
  float Xfrac = x - Xint;
  float Yfrac = y - Yint;
  float Zfrax = z - Zint;
  //noise values
  float n01 = Noise(Xint-1, Yint-1);
  float n02 = Noise(Xint+1, Yint-1);
  float n03 = Noise(Xint-1, Yint+1);
  float n04 = Noise(Xint+1, Yint+1);
  float n05 = Noise(Xint-1, Yint);
  float n06 = Noise(Xint+1, Yint);
  float n07 = Noise(Xint, Yint-1);
  float n08 = Noise(Xint, Yint+1);
  float n09 = Noise(Xint, Yint);

  float n12 = Noise(Xint+2, Yint-1);
  float n14 = Noise(Xint+2, Yint+1);
  float n16 = Noise(Xint+2, Yint);

  float n23 = Noise(Xint-1, Yint+2);
  float n24 = Noise(Xint+1, Yint+2);
  float n28 = Noise(Xint, Yint+2);

  float n34 = Noise(Xint+2, Yint+2);

  //find the noise values of the four corners
  float x0y0 = 0.0625*(n01+n02+n03+n04) + 0.125*(n05+n06+n07+n08) + 0.25*(n09);  
  float x1y0 = 0.0625*(n07+n12+n08+n14) + 0.125*(n09+n16+n02+n04) + 0.25*(n06);  
  float x0y1 = 0.0625*(n05+n06+n23+n24) + 0.125*(n03+n04+n09+n28) + 0.25*(n08);  
  float x1y1 = 0.0625*(n09+n16+n28+n34) + 0.125*(n08+n14+n06+n24) + 0.25*(n04);  

  //interpolate between those values according to the x and y fractions
  float v1 = Interpolate(x0y0, x1y0, Xfrac); //interpolate in x direction (y)
  float v2 = Interpolate(x0y1, x1y1, Xfrac); //interpolate in x direction (y+1)
  float fin = Interpolate(v1, v2, Yfrac);  //interpolate in y direction

  return fin;
}
float Interpolate(float x, float y, float a)
{
  float negA = 1.0 - a;
  float negASqr = negA * negA;
  float fac1 = 3.0 * (negASqr) - 2.0 * (negASqr * negA);
  float aSqr = a * a;
  float fac2 = 3.0 * aSqr - 2.0 * (aSqr * a);

  return x * fac1 + y * fac2; //add the weighted factors
}

float Noise(int x, int y)
{
  return noise1(vec2(x,y));
  int n = x + y * 57;
  n = (n << 13) ^ n;
  int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
  return 1.0 - float(t) * 0.931322574615478515625e-9;/// 1073741824.0);
}

float Noise(int x, int y,int z)
{
  //return noise1(vec2(x,y));
  int n = x + y * 57+z*865;
  n = (n << 13) ^ n;
  int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
  return 1.0 - float(t) * 0.931322574615478515625e-9;/// 1073741824.0);
}






const int X_NOISE_GEN = 1619;
const int Y_NOISE_GEN = 31337;
const int Z_NOISE_GEN = 6971;
const int SEED_NOISE_GEN = 1013;
const int SHIFT_NOISE_GEN = 8;

  float LinearInterp (float n0, float n1, float a)
  {
    return ((1.0 - a) * n0) + (a * n1);
  }

float GradientNoise3D (float fx, float fy, float fz, int ix,
  int iy, int iz, int seed)
{
  // Randomly generate a gradient vector given the integer coordinates of the
  // input value.  This implementation generates a random number and uses it
  // as an index into a normalized-vector lookup table.
  int vectorIndex = int(uint(1619    * ix    + 31337    * iy    + 6971    * iz    + 1013 * seed) & 0xffffffff);
  vectorIndex ^= (vectorIndex >> SHIFT_NOISE_GEN);
  vectorIndex &= 0xff;
  int index = (vectorIndex << 2);
  float xvGradient = g_randomVectors[index].x;
  float yvGradient = g_randomVectors[index].y;
  float zvGradient = g_randomVectors[index].z;

  // Set up us another vector equal to the distance between the two vectors
  // passed to this function.
  float xvPoint = (fx - float(ix));
  float yvPoint = (fy - float(iy));
  float zvPoint = (fz - float(iz));

  // Now compute the dot product of the gradient vector with the distance
  // vector.  The resulting value is gradient noise.  Apply a scaling value
  // so that this noise value ranges from -1.0 to 1.0.
  return ((xvGradient * xvPoint)
    + (yvGradient * yvPoint)
    + (zvGradient * zvPoint)) * 2.12;
}


  float fmod(float value,float divid)
  {
    return (value/divid-int(value/divid))*divid;
  }
  float MakeInt32Range (float n)
  {
    if (n >= 1073741824.0) {
      return (2.0 * fmod (n, 1073741824.0)) - 1073741824.0;
    } else if (n <= -1073741824.0) {
      return (2.0 * fmod (n, 1073741824.0)) + 1073741824.0;
    } else {
      return n;
    }
  }

float GradientCoherentNoise3D (float x, float y, float z, int seed)
{
  // Create a unit-length cube aligned along an integer boundary.  This cube
  // surrounds the input point.
  int x0 = (x > 0.0? int(x): int(x) - 1);
  int x1 = x0 + 1;
  int y0 = (y > 0.0? int(y): int(y) - 1);
  int y1 = y0 + 1;
  int z0 = (z > 0.0? int(z): int(z) - 1);
  int z1 = z0 + 1;

  // Map the difference between the coordinates of the input value and the
  // coordinates of the cube's outer-lower-left vertex onto an S-curve.
  float xs = 0, ys = 0, zs = 0;

  xs = (x - float(x0));
  ys = (y - float(y0));
  zs = (z - float(z0));
  
  float n0, n1, ix0, ix1, iy0, iy1;
  n0   = GradientNoise3D (x, y, z, x0, y0, z0, seed);
  n1   = GradientNoise3D (x, y, z, x1, y0, z0, seed);
  ix0  = LinearInterp (n0, n1, xs);
  n0   = GradientNoise3D (x, y, z, x0, y1, z0, seed);
  n1   = GradientNoise3D (x, y, z, x1, y1, z0, seed);
  ix1  = LinearInterp (n0, n1, xs);
  iy0  = LinearInterp (ix0, ix1, ys);
  n0   = GradientNoise3D (x, y, z, x0, y0, z1, seed);
  n1   = GradientNoise3D (x, y, z, x1, y0, z1, seed);
  ix0  = LinearInterp (n0, n1, xs);
  n0   = GradientNoise3D (x, y, z, x0, y1, z1, seed);
  n1   = GradientNoise3D (x, y, z, x1, y1, z1, seed);
  ix1  = LinearInterp (n0, n1, xs);
  iy1  = LinearInterp (ix0, ix1, ys);

  return LinearInterp (iy0, iy1, zs);
}



float GetValue (float x, float y, float z)
{
  float value = 0.0;
  float signal = 0.0;
  float curPersistence = 1.0;
  float nx, ny, nz;
  int seed;

  x *= frequency;
  y *= frequency;
  z *= frequency;

  for (int curOctave = 0; curOctave < octaves; curOctave++) {

    // Make sure that these floating-point values have the same range as a 32-
    // bit integer so that we can pass them to the coherent-noise functions.
    nx =  MakeInt32Range(x);
    ny =  MakeInt32Range(y);
    nz =  MakeInt32Range(z);

    // Get the coherent-noise value from the input value and add it to the
    // final result.
    seed = int(uint(randomseed + curOctave) & 0xffffffff);
    signal = GradientCoherentNoise3D (nx,ny,nz,seed);
    value += signal * curPersistence;

    // Prepare the next octave.
    x *= lacunarity;
    y *= lacunarity;
    z *= lacunarity;
    curPersistence *= persistence;
  }

  return value;
}*/



#endif /* _PERLIN3_GLSL_ */ 