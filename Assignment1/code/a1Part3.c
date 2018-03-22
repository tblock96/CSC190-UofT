#include "a1.h"

void simpsonsAdaptiveIntegration(float aOrig, float bOrig, float eps, float minIntSize)
{
//an array holds the bounds of integration. aOrig and bOrig are not
//stored in the array. The function iterates through the array,
//comparing numerical integration values and adding an element to
//the array for the next iteration if the error is too large.
//The question becomes how to store the elements in the array.
//
//We could insert them, either using a built-in insert function
//(if it exists), or writing our own, or we could use a binary tree
//format, with areas of the array getting filled in that need more
//divisions. Let's try that one and see how it goes.
//
//The way loops work in C make it so that inserting is way way
//easier. So we will now try that.
	float A[ARRAYSIZE];
	int i, j; float res = 0.0;
	// Defining the default values of A
	A[0] = aOrig; A[1] = bOrig;
	for(i=2;i<ARRAYSIZE;i++) {
		A[i] = 10000;
	}
	// Running the real 'functional' part of the function
	i=0;
	while(A[i+1]!=10000) {
		float a=A[i], b=A[i+1], m=(a+b)/2;
		float err = (S(a,m)+S(m,b)-S(a,b))/15;
		if (err < 0.0 && (b-a)>minIntSize)  err = -err; // Redneck abs()
		if(err >= eps && (b-a)>minIntSize) {
			// INSERT MIDPOINT
			// ADD 1 to the index of all list
			// elements greater than m
			if(A[ARRAYSIZE-1]!=10000) {
				printf("Error: Too many subintervals. ARRAYSIZE");
				printf(" is too small.\nDisregard the result below.\n");
				break;				
			}
			for(j=ARRAYSIZE-2;j>i;j--)
				A[j+1] = A[j];
			// Now put midpoint at i+1
			A[i+1] = m;
			// Don't move i in this case
		} else {
			res += S(A[i], A[i+1]);
			i++;
		}
	}
	printf("Result is: %f\n", res);
}
