#include "../headers/Salesman.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

long factorial(long n);

Salesman salesman;
long currentIndex = 0;
double targetIndex;

long factorial(long n) {
	if(n < 0)
		return n * factorial(abs(n)-1);
	if(n <= 1)
		return 1;
	return n * factorial(n - 1);
}	
void init(int num) {
	Route *route = routeInit(num);
	salesman.startingRoute = route;
	
	salesman.bestRoute = routeInitFromCities(route->cities, num);
	salesman.bestDistance = route->distance;
	
	salesman.worstRoute = routeInitFromCities(route->cities, num);
	salesman.worstDistance = route->distance;
}
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

void evaluateRoute(Route *route) {
	calcDistance(route);
	if(route->distance < salesman.bestDistance) {
		salesman.bestDistance = route->distance;
		for(int i = 0; i < route->numberOfCities; i++)
			salesman.bestRoute->cities[i] = route->cities[i]; 
	}
	else if(route->distance > salesman.worstDistance) {
		salesman.worstDistance = route->distance;
		for(int i = 0; i < route->numberOfCities; i++)
			salesman.worstRoute->cities[i] = route->cities[i]; 
	}
	if(currentIndex % 1000000 == 0 || currentIndex == 0) {
		printf("%f%%\r",currentIndex/targetIndex);
	}
	currentIndex++;
}
void printRoute(Route *route) {
	for(int i = 0; i < route->numberOfCities; i++) {
		printf("%c ",route->cities[i]->id);
	}
	printf("%c %f\n",route->cities[0]->id, getDistance(route));
}
void freeSalesman() {
	freeRoute(salesman.startingRoute);
	freeRoute(salesman.bestRoute);
	freeRoute(salesman.worstRoute);
}
int main(int nArgs, char **args) {
	if(nArgs == 2) {
		const int num = atoi(args[1]);
		init(num);
		targetIndex = factorial(num-1)/100;
		printf("Computation time: %f seconds\n",compute());
		freeSalesman();
		}
	else
		printf("Requires argument for number of cities\n");
}