#include "../headers/Route.h"
#include <stdlib.h>
#include <stdio.h>

double randNum() {
	double range = 20 - 0;
	double div = RAND_MAX / range;
	return rand() / div;
}
Route *routeInit(int num) {
	Route *route = (Route*)calloc(sizeof(Route),1);
	route->cities = (City**)malloc(sizeof(City*)*num); //Valgrand is reporting this memory not being freed
	route->numberOfCities = num;
	char current = 'A';
	for(int i = 0; i < num; i++, current++) {
		route->cities[i] = cityInit(randNum(), randNum(), current);
	}
	route->distance = calcDistance(route);
	return route;
}
Route *routeInitFromCities(City **cities, int num) {
	Route *route = (Route*)calloc(sizeof(Route),1);
	route->cities = cities;
	route->numberOfCities = num;
	route->distance = calcDistance(route);
	return route;
}
double calcDistance(Route *route) {
	double distance = 0.0;
	for(int i = 0; i < route->numberOfCities; i++) {
		if(i < route->numberOfCities-1) 
			distance += distanceBetween(route->cities[i], route->cities[i+1]);
		else
			distance += distanceBetween(route->cities[i], route->cities[0]);
	}
	return distance;
}
void freeRoute(Route *route) {
	for(int i = 0; i < route->numberOfCities; i++) {
		if(route->cities[i] != NULL) 
			free(route->cities[i]);
		route->cities[i] = NULL;
	}
	free(route);	
}