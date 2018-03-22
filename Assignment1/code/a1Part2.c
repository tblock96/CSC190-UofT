#include "a1.h"

float S(float a, float b)
{
	return (b-a)/6*(f(a) +4*f((b+a)/2) + f(b));   
}
