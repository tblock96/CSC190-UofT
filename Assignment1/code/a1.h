#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define ARRAYSIZE 1000

float f(float x);
void simpsonsAdaptiveIntegration(float aOrig, float bOrig, float eps, float minIntSize);
float S(float a, float b);
float simpsonsAdaptiveIntegrationR(float a, float b, float eps, float minIntSize);
