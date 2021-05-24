#ifndef FIXED_MATH_H
#define FIXED_MATH_H

#include <math.h>
#include <stdint.h>

typedef int32_t fixed_t;

fixed_t int2fixed_t(int16_t x);
fixed_t float2fixed_t(float x);
int32_t fraction2fixed_t(int32_t a,int32_t b);
fixed_t fixdiv(fixed_t a,fixed_t b);
fixed_t fixmul(fixed_t a,fixed_t b);
int32_t fixed2int(fixed_t x);
float fixed2float(fixed_t x);
fixed_t fixabs(fixed_t x);
fixed_t frac(fixed_t x);

#endif

