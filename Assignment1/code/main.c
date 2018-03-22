#include "a1.h"

int main( int argc, char *argv[] )
{
    if( argc < 2 || argc > 2)
   	{
        printf("Expecting only one argument. Please try again\n");
   	}
    else
    {
        if(atoi(argv[1])==1)
        {
            printf("Result of Part 1 is %f \n",f(2.1));
        }
        else if(atoi(argv[1])==2)
        {
            printf("Result of Part 2 is %f \n",S(-M_PI/2,M_PI/12));
        }
        else if(atoi(argv[1])==3)
        {
            simpsonsAdaptiveIntegration(-M_PI/2,M_PI/12,0.0000001,0.0000001);
        }
        else
        {
            printf("Incorrect argument supplied.\n");
        }
    }
    return 0;
}
