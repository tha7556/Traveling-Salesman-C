#include "../headers/Route.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
void initDistMat(City ** cities, int num);

int freed = 0;
double ** distMat;
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
	if(!distMat) {
		initDistMat(route->cities, num);
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
void initDistMat(City **cities, int num) {
	distMat = malloc(sizeof(City*) * num);
	for(int i = 0; i < num; i++) {
		distMat[i] = malloc(sizeof(City) * num);
		for(int j = 0; j < num; j++) {
			distMat[cities[i]->id-'A'][cities[j]->id-'A'] = distanceBetween(cities[i], cities[j]);
		}
	}
}
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
double getDistance(Route *route) {
	calcDistance(route);
	return sqrt(route->distance);
}
void freeDistMat(int num) {
	for(int i = 0; i < num; i++) {
		free(distMat[i]);
	}
	free(distMat);
}
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