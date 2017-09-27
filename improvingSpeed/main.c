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
double taylorSin(double x);
double improvedTaylorSin(double x); 
double rawSumAndAverage64(double x);
double improvedSumAndAverage64(double x);

int main(int argc, char *argv) {
	// Greets to user
	printf("Hello! This code calculates a Sin(x) many times.\n");
	printf("Check this out!\n");
	
	double x; // Input for sin function
	x = PI/4;
	
	// Benchmark functions	
	int m = 1000,  n = 50;
	double clocks1, clocks2, clocks3, improvement;

    printf("=======================================================\n");
    printf("==> Benchmark of separated functions <==\n");
    printf("=======================================================\n");
    clocks1 = calcAverageTime(m, n, &rawSin, x);
    clocks2 = calcAverageTime(m, n, &taylorSin, x); 
    clocks3 = calcAverageTime(m, n, &improvedTaylorSin, x); 

    printf("Result for rawSin is %lf. \n", rawSin(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n\n", m, n, clocks1);		
	
	printf("Result for taylorSin is %lf. \n", taylorSin(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n\n", m, n, clocks2);		
	
	printf("Result for improvedTaylorSin is %lf. \n", improvedTaylorSin(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n\n", m, n, clocks3);		
	
    improvement = (clocks1 - clocks3) * 100.0 / clocks1;
    printf("Overral improvement has value of %.2lf percent.\n", improvement);

    
    printf("=======================================================\n");
    printf("==> Benchmark of mixed functions, including module, average and division by constant <==\n");
    printf("=======================================================\n");
    clocks1 = calcAverageTime(m, n, &rawSumAndAverage64, x);
    clocks2 = calcAverageTime(m, n, &improvedSumAndAverage64, x); 

    printf("Result for rawSumAndAverage64 is %lf. \n", rawSumAndAverage64(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n\n", m, n, clocks1);		
	
	printf("Result for improvedSumAndAverage64 is %lf. \n", improvedSumAndAverage64(x));
    printf("Average for %i calls by %i samples is: %.2f clock cycles\n\n", m, n, clocks2);		
    
    improvement = (clocks1 - clocks2) * 100.0 / clocks1;
    printf("Overral improvement has value of %.2lf percent.\n", improvement);
 	
}

// Raw sin function
double rawSin(double x)  {
	return sin(x);
}

// Using a 4rd grade Taylor Series approximation
double taylorSin(double x) {
	return x - x*x*x / 6.0  + x*x*x*x*x / 120.0 - x*x*x*x*x*x*x / 5040.0;
}

// Improving calculations by using divide by constant and shift
double improvedTaylorSin(double x) {
	return  (x*104*(5040 + x*(-840*x + x*x*x*(42 - x*x) ) ) ) / pow(2,19);
}


// Mixing module function and division by constant on the dumb way
double rawSumAndAverage64(double x) {
	double accum = 0;
	double value[8];
	double average;
	int i;
	for(i = 0; i < 64; ++i) {
		value[i % 8] = rawSin(x * (i % 4) );
		accum += value[i % 8];
	}
	average = accum / 64;
	return average;	
}

// Mixing module function and division by constant on smart way
double improvedSumAndAverage64(double x) {
	double accum = 0;
	double value[8];
	double average;
	int i;
	for(i = 0; i < 64; ++i) {
		value[i & 0b111] = improvedTaylorSin(x * (i & 0b11) );
		accum += value[i & 0b111];
	}
	average = accum / 64;
	return average;	
}

// Execute calcTime m times and take the clock consumption average
double calcAverageTime(int m, int n, double (*f)(double),  double x) {
	double clocksTaken = 0;
	int i;
	for(i = 0; i < m; ++i) {
		clocksTaken += calcTime(n, f, x);		
	}
	return (double) clocksTaken / m;
}

// Execute the function f n times and take the number of clocks taken
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
