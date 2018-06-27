#include "../headers/Salesman.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Salesman salesman;
long i = 0;

void init(int num) {

	Route *route = routeInit(num);
	salesman.startingRoute = routeInitFromCities(route->cities, num);
	salesman.bestRoute = route;
	salesman.bestFitness = route->distance;
}
void go(int low) {
	if(low + 1 >= salesman.startingRoute->numberOfCities) 
		evaluateRoute(salesman.startingRoute);
	else {
		go(low + 1);
		for(int i = low + 1; i < salesman.startingRoute->numberOfCities; i++) {
			City *temp = salesman.startingRoute->cities[low];
			salesman.startingRoute->cities[low] = salesman.startingRoute->cities[i];
			salesman.startingRoute->cities[i] = temp;
			go(low + 1);
			temp = salesman.startingRoute->cities[low];
			salesman.startingRoute->cities[low] = salesman.startingRoute->cities[i];
			salesman.startingRoute->cities[i] = temp;
		}
	}
}
double compute() {
	clock_t start = clock();
	go(1);
	printf("\ni: %ld\n",i);
	clock_t end = clock();
	return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void evaluateRoute(Route *route) {
	if(i % 10000 == 0) {
		for(int i = 0; i < route->numberOfCities; i++) {
			printf("%c ", route->cities[i]->id);
		}
		printf("%c\r",route->cities[0]->id);
		}
	i++;
}
void freeSalesman() {
	freeRoute(salesman.startingRoute);
	freeRoute(salesman.bestRoute);
}
int main(int nArgs, char **args) {
	if(nArgs == 2) {
		const int num = atoi(args[1]);
		init(num);
		printf("Computation time: %f seconds\n",compute());
		freeSalesman();
		printf("End!\n");
	}
	else
		printf("Requires argument for number of cities\n");
}