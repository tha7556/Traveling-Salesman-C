#include "../headers/Route.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int freed = 0; //A boolean to determine if the cities have been freed yet. Should only be modified inside of freeRoute
double ** distMat;

/**
* Generates a random number between 2 numbers. Used to randomly initialize the cities
* @param low The lower limit
* @param high The upper limit
* @return The resulting random number
*/
static double randNum(int low, int high) {
	double range = high - low;
	double div = RAND_MAX / range;
	return rand() / div;
}
/** 
* Initializes the Distance Matrix, which is used when calculating the distance of a route.
* The Distance Matrix contains the distance from every city to every other city
* @param cities The array of pointers to the cities
* @param num The number of cities
*/
static void initDistMat(City **cities, int num) {
	distMat = malloc(sizeof(City*) * num);
	for(int i = 0; i < num; i++) {
		distMat[i] = malloc(sizeof(City) * num);
		for(int j = 0; j < num; j++) {
			distMat[cities[i]->id-'A'][cities[j]->id-'A'] = distanceBetween(cities[i], cities[j]);
		}
	}
}
/**
* Initializes the route based on the number of cities. Also creates the City objects used. 
* As it allocates the Cities it is recommended to only use this initializer once per Salesman, and use the alternate initializer for other routes.
* @param num The number of cities
* @return A pointer to the created Route
*/
Route *routeInit(int num) {
	srand(time(NULL)); //Seed for random, if removed it will always be the same sequence. Could be useful debug?
	Route *route = (Route*)calloc(sizeof(Route),1);
	route->cities = (City**)malloc(sizeof(City*)*num);
	route->numberOfCities = num;
	char current = 'A';
	for(int i = 0; i < num; i++, current++) {
		route->cities[i] = cityInit(randNum(1000,0), randNum(1000,0), current);
	}
	if(!distMat) {
		initDistMat(route->cities, num);
	}
	calcDistance(route);
	return route;
}
/**
* An alternate initializer based on an array of pointers to cities that have already been created. 
* @param cities An array of pointers to cities
* @param numberOfCities The total number of cities
* @return A pointer to the created Route
*/
Route *routeInitFromCities(City **cities, int num) {
	Route *route = (Route*)calloc(sizeof(Route),1);
	route->cities = (City**)malloc(sizeof(City*)*num);
	for(int i = 0; i < num; i++) {
		route->cities[i] = cities[i];
	}
	route->numberOfCities = num;
	calcDistance(route);
	return route;
}

/**
* Calculates the total distance of the Route. The result is stored in the route->distance
* @param route The route to calculate the distance for.
*/
void calcDistance(Route *route) {
	double distance = 0.0;
	for(int i = 0; i < route->numberOfCities; i++) {
		if(i < route->numberOfCities-1) 
			distance += distMat[route->cities[i]->id-'A'][route->cities[i+1]->id-'A'];
		else
			distance += distMat[route->cities[i]->id-'A'][route->cities[0]->id-'A'];
	}
	route->distance = distance;
}
/**
* Prints the id for each city, as well as the total distance to the console
* @param route The Route to print
*/
void printRoute(Route *route) {
	for(int i = 0; i < route->numberOfCities; i++) {
		printf("%c ",route->cities[i]->id);
	}
	printf("%c %f\n",route->cities[0]->id, route->distance);
}
/**
* Frees the memory used by the Distance Matrix
* @param The number of cities
*/
static void freeDistMat(int num) {
	for(int i = 0; i < num; i++) {
		free(distMat[i]);
	}
	free(distMat);
}
/**
* Frees the Route and all of its cities if they have not been freed yet.
* @param route The Route to free
*/
void freeRoute(Route *route) {
	if(freed == 0) {
		freeDistMat(route->numberOfCities);
		for(int i = 0; i < route->numberOfCities; i++) {
			free(route->cities[i]);
		}
		freed = 1;
	}
	free(route->cities);
	free(route);	
}