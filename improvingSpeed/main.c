#include<stdint.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include"rdtsc.h"

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)
#define PI 3.14159265

unsigned long long calcTime(int n, double (*f)(double) , double x) ;	// Execute f(x) for n times, then return time
double calcAverageTime(int m, int n, double (*f)(double),  double x) ; // Calculate average for m executions of calcTime
double rawSin(double x);
double rawTaylorSin(double x);


int main(int argc, char *argv) {
	// Greets to user
	printf("Hello! This code calculates a Sin(x) many times.\n");
	printf("Check this out!\n");
	
	double x; // Input for sin function
	x = PI/2;
	
	// Benchmark functions	
	int m = 10,  n = 1000;
	printf("Result for rawSin is %lf. \n", rawSin(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n", m, n, calcAverageTime(m, n, &rawSin, x));		
	
	printf("Result for rawTaylorSin is %lf. \n", rawTaylorSin(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n", m, n, calcAverageTime(m, n, &rawTaylorSin, x) );		
	
}

// Using a 3rd grade Taylor Series approximation
double rawTaylorSin(double x) {
	return x - x*x*x / (6.0) + x*x*x*x*x / (120.0);
}

// Raw sin function
double rawSin(double x)  {
	return sin(x);
}

double calcAverageTime(int m, int n, double (*f)(double),  double x) {
	double clocksTaken = 0;
	int i;
	for(i = 0; i < m; ++i) {
		clocksTaken += calcTime(n, f, x);		
	}
	return (double) clocksTaken / m;
}

unsigned long long calcTime(int n, double (*f)(double) , double x)  {
	// Initialize variables
	unsigned long long start, end;
	double result;
	int counter = n;
	
	// Start time and execute function	
	start = rdtsc();
	while(--counter > 0 ) {
		result =  (*f)(x) ;
	}
	end = rdtsc();
	
	// Print results
	unsigned long long clocksTaken = ( end - start );
	//printf("%u clocks taken\n", clocksTaken);
	
	return clocksTaken;
	
}
