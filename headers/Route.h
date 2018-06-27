#ifndef ROUTE_H
#define ROUTE_H
#include "City.h"

typedef struct Route_t {
	City **cities;
	int numberOfCities;
	double distance;
}Route;

Route *routeInit(int num);
Route *routeInitFromCities(City **cities, int numberOfCities);
void calcDistance(Route *route);
double getDistance(Route *route);
//Frees the pointer to the route as well as all of the cities contained by it
void freeRoute(Route *route);

#endif