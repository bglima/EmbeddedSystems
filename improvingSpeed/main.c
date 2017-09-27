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
double rawSumAndAverage64(double x);
double taylorSumAndAverage64(double x);

int main(int argc, char *argv) {
	// Greets to user
	printf("Hello! This code calculates a Sin(x) many times.\n");
	printf("Check this out!\n");
	
	double x; // Input for sin function
	x = PI/4;
	
	// Benchmark functions	
	int m = 10,  n = 1000;
	printf("Result for rawSin is %lf. \n", rawSin(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n\n", m, n, calcAverageTime(m, n, &rawSin, x));		
	
	printf("Result for taylorSin is %lf. \n", taylorSin(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n\n", m, n, calcAverageTime(m, n, &taylorSin, x) );		
	
	printf("Result for rawSumAndAverage64 is %lf. \n", rawSumAndAverage64(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n\n", m, n, calcAverageTime(m, n, &rawSumAndAverage64, x) );		
	
	printf("Result for taylorSumAndAverage64 is %lf. \n", taylorSumAndAverage64(x));
	printf("Average for %i calls by %i samples is: %.2f clock cycles\n\n", m, n, calcAverageTime(m, n, &taylorSumAndAverage64, x) );		
	
}

// Raw sin function
double rawSin(double x)  {
	return sin(x);
}

// Using a 3rd grade Taylor Series approximation
double taylorSin(double x) {
	// return x - x*x*x / (6.0) + x*x*x*x*x / (120.0);
	return x*(120 - x*(x*20 + x*x*x))/120.0;
}

// Mixing module function and division by constant on the dumb way
double rawSumAndAverage64(double x) {
	double accum = 0;
	double value[8];
	double average;
	int i;
	for(i = 0; i < 64; ++i) {
		value[i % 8] = rawSin(x * i);
		//printf("Com modulo: %i\n", i % 8);
		//printf("Com Bitmaks: %i\n", (int)i & 0b111);
		accum += value[i % 8];
//		printf("Value %lf  %lf\n", value[i%8], value[(int)i & 0b111]);
	}
	average = accum / 64;
	return average;	
}

// Mixing module function and division by constant on smart way
double taylorSumAndAverage64(double x) {
	double accum = 0;
	double value[8];
	double average;
	int i;
	for(i = 0; i < 64; ++i) {
		value[i & 0b111] = taylorSin(x * i);
		//printf("Com modulo: %i\n", i % 8);
		//printf("Com Bitmaks: %i\n", (int)i & 0b111);
		accum += value[i & 0b111];
//		printf("Value %lf  %lf\n", value[i%8], value[(int)i & 0b111]);
	}
	average = accum / 64;
	return average;	
}




// We need do transform 1/120.0 into a sfhit. Thus, we have to:
// 1 - Multiply the constant with 100
// 2 - Find the smallest power of two, that is bigger than the product. In this case, bigger than 12000 = 2^11 = 2048. This is the denominator
// 3 - Divide the denominator by the initial constant. In this case, 2048 / 120 ~= 17
// Finally, we found: 1 / 120.0 ~= 17 / 2048
double improvedTaylor2(double x) {
	//return (int)(x*17*(120 - x*x*20 + x*x*x*x) )>> 11;
	return 0;
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
