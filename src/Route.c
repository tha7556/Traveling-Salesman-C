#include "../headers/Route.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
int freed = 0;
double randNum() {
	double range = 1000 - 0;
	double div = RAND_MAX / range;
	return rand() / div;
}
Route *routeInit(int num) {
	srand(time(NULL)); //Seed for random, if removed it will always be the same sequence. Could be useful debug?
	Route *route = (Route*)calloc(sizeof(Route),1);
	route->cities = (City**)malloc(sizeof(City*)*num);
	route->numberOfCities = num;
	char current = 'A';
	for(int i = 0; i < num; i++, current++) {
		route->cities[i] = cityInit(randNum(), randNum(), current);
	}
	calcDistance(route);
	return route;
}
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
void calcDistance(Route *route) {
	double distance = 0.0;
	for(int i = 0; i < route->numberOfCities; i++) {
		if(i < route->numberOfCities-1) 
			distance += distanceBetween(route->cities[i], route->cities[i+1]);
		else
			distance += distanceBetween(route->cities[i], route->cities[0]);
	}
	route->distance = distance;
}
double getDistance(Route *route) {
	calcDistance(route);
	return sqrt(route->distance);
}
void freeRoute(Route *route) {
	if(freed == 0) {
		for(int i = 0; i < route->numberOfCities; i++) {
			free(route->cities[i]);
		}
		freed = 1;
	}
	free(route->cities);
	free(route);	
}