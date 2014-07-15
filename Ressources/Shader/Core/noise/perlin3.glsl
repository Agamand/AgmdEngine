
#ifndef _PERLIN3_GLSL_
#define _PERLIN3_GLSL_

#include "perlin.glsl"
#include "noise_table.glsl"
/*
	LIBnoise conversion c++ to glsl

*/


float persistence = 0.5f, frequency = 0.2f, amplitude = 1.f,
lacunarity = 2.0f;
int octaves = 8, randomseed = 5465463;


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
    nx =  (x);
    ny =  (y);
    nz =  (z);

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
}



#endif /* _PERLIN3_GLSL_ */ 