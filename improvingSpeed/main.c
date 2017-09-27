#include<stdint.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)
#define PI 3.14159265

double calcTime(int n, double (*f)(double) , double x) ;	// Execute f(x) for n times, then return time
double calcAverageTime(int m, int n, double (*f)(double),  double x) ; // Calculate average for m executions of calcTime
double rawSin(double x);

int main(int argc, char *argv) {
	// Greets to user
	printf("Hello! This code calculates a Sin(x) many times.\n");
	printf("Check this out!\n");
	
	double x; // Input for sin function
	x = PI/2;
	
	// Benchmark functions	
	printf("Average time was %f milliseconds\n", calcAverageTime(200, 2*10E4, &rawSin, x));		
}

double calcTime(int n, double (*f)(double) , double x)  {
	// Initialize variables
	clock_t start, end;
	double result;
	int counter = n;
	
	// Start time and execute function	
	start = clock();
	while(--counter > 0 ) {
		result =  (*f)(x) ;
	}
	end = clock();
	
	// Print results
	double timeTaken = ((double)( end - start )) / CLOCKS_PER_MS;
	//printf("Result for sin(%lf) is: %lf\n", x, result);	
	printf("It took %lf milliseconds to execute %i times.\n", timeTaken, n);
	
	return timeTaken;
	
}

double rawSin(double x)  {
	return sin(x);
}

double calcAverageTime(int m, int n, double (*f)(double),  double x) {
	double totalTime = 0;
	int i;
	for(i = 0; i < m; ++i)
		totalTime += calcTime(n, f, x);
	return totalTime / m;
}
