#include<stdint.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)
#define PI 3.14159265

double rawSin(double x)  {
	return sin(x);
}


// Exexcute the function "f(x)"  for "counter" times
void calculateTime(int n, double (*f)(double) , double x)  {
	// Initialize variables
	clock_t start, end;
	double result;
	int counter = n;
	
	// Start time and execute function
	printf("Initiating timer...\n");
	
	start = clock();
	while(--counter > 0 ) {
		result =  (*f)(x) ;
	}
	end = clock();
	
	// Print results
	printf("Result for sin(%lf) is: %lf\n", x, result);	
	double timeTaken = ((double)( end - start )) / CLOCKS_PER_MS;
	printf("It took %lf milliseconds to execute %i times.\n", timeTaken, n);
	
}

int main(int argc, char *argv) {
	// Greets to user
	printf("Hello! This code calculates a Sin(x) many times.\n");
	printf("Check this out!\n");
	
	double x; // Input for sin function
	x = PI/2;
	
	// Benchmark functions	
	calculateTime(10E6, &rawSin, x);		
}

