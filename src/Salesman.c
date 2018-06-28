#include "../headers/Salesman.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

Salesman salesman;
long long currentIndex = 0;
double targetIndex;

/**
* Finds the factorial of the given number. Used to find the targetIndex which is used to calculate the progress percent
* @param n The number to find the factorial of
* @return The factorial of the number
*/
static long long factorial(long n) {
	if(n < 0)
		return n * factorial(abs(n)-1);
	if(n <= 1)
		return 1;
	return n * factorial(n - 1);
}	
/**
* Initializes the Salesman, and all of its Routes based on the given number of cities
* @param num The number of cities
*/
void init(int num) {
	Route *route = routeInit(num);
	salesman.startingRoute = route;
	
	salesman.bestRoute = routeInitFromCities(route->cities, num);
	salesman.worstRoute = routeInitFromCities(route->cities, num);
	
	targetIndex = factorial(num-1)/100.0;
}
/** 
* A recursive function which calculates each permutation of the starting route and calls evaluateRoute on each one
* @param low The current index of the recursive method
*/
void go(int low) {
	if(low + 1 >= salesman.startingRoute->numberOfCities) {
		evaluateRoute(salesman.startingRoute);
	}
	else {
		go(low + 1);
		for(int i = low + 1; i < salesman.startingRoute->numberOfCities; i++) {
			//Swap
			City *temp = salesman.startingRoute->cities[low];
			salesman.startingRoute->cities[low] = salesman.startingRoute->cities[i];
			salesman.startingRoute->cities[i] = temp;
			go(low + 1);
			//Swap
			temp = salesman.startingRoute->cities[low];
			salesman.startingRoute->cities[low] = salesman.startingRoute->cities[i];
			salesman.startingRoute->cities[i] = temp;
		}
	}
}
/**
* Starts the process of finding the best and worst routes through exhaustive search. Returns the number of seconds that were taken for this process
* @return The total number of seconds taken evaluate every permutation of the route
*/
double compute() {
	clock_t start = clock();
	go(1);
	clock_t end = clock();
	
	printf(" Best Route: "); 
	printRoute(salesman.bestRoute);	
	printf("Worst Route: "); 
	printRoute(salesman.worstRoute);
	
	return ((double)(end - start)) / CLOCKS_PER_SEC;
}
/**
* Evaluates a single route by comparing it against both the best and worst routes
* @param route A pointer to the route being evaluated
*/
void evaluateRoute(Route *route) {
	calcDistance(route);
	if(route->distance < salesman.bestRoute->distance) {
		salesman.bestRoute->distance = route->distance;
		for(int i = 0; i < route->numberOfCities; i++) {
			salesman.bestRoute->cities[i] = route->cities[i]; 
			
		}
	}
	else if(route->distance > salesman.worstRoute->distance) {
		salesman.worstRoute->distance = route->distance;
		for(int i = 0; i < route->numberOfCities; i++) {
			salesman.worstRoute->cities[i] = route->cities[i]; 
			
		}
	}
	else if(currentIndex % 1000000 == 0 || currentIndex == 0) {
		printf("%f%%\r",currentIndex/targetIndex);
	}
	currentIndex++;
}
/**
* Formats the number of seconds into a string, dividing the seconds into hours and minutes
* @param seconds The number of seconds
* @return A string representation of the time, divided into hours and minutes
*/
char *formatTime(double seconds) {
	int hours = 0, minutes = 0;
	double secs = seconds;
	char *result = (char*)malloc(sizeof(char) * 45);
	if(seconds < 60)
		sprintf(result, "%.2f seconds",seconds);
	else {
		while(secs >= 60) {
			secs -= 60;
			minutes++;
		}
		while(minutes >= 60) {
			minutes -= 60;
			hours++;
		}
		if(hours == 0) 
			sprintf(result, "%d minutes, %.2f seconds", minutes, secs);
		else
			sprintf(result, "%d hours, %d minutes, %f.2 seconds", hours, minutes, secs);
	}		
	return result;
}
/**
* Frees the memory used by the Salesman and all of the routes and cities
*/
void freeSalesman() {
	freeRoute(salesman.startingRoute);
	freeRoute(salesman.bestRoute);
	freeRoute(salesman.worstRoute);
}
/**
* Usage: ./Salesman {number of cities}
*/
int main(int nArgs, char **args) {
	if(nArgs == 2) {
		const int num = atoi(args[1]);
		init(num);
		char *time = formatTime(compute());
		printf("Computation time: %s\n",time);
		free(time);
		freeSalesman();
	}
	else
		printf("Requires argument for number of cities\n");
}