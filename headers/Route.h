#ifndef ROUTE_H
#define ROUTE_H
#include "City.h"
/**
* A Route object that contains an array of pointers to Cities, the total number of cities, and the route's distance
*/
typedef struct Route_t {
	City **cities;
	int numberOfCities;
	double distance;
}Route;
/**
* Initializes the route based on the number of cities. Also creates the City objects used. 
* As it allocates the Cities it is recommended to only use this initializer once per Salesman, and use the alternate initializer for other routes.
* @param num The number of cities
* @return A pointer to the created Route
*/
Route *routeInit(int num);
/**
* An alternate initializer based on an array of pointers to cities that have already been created. 
* @param cities An array of pointers to cities
* @param numberOfCities The total number of cities
* @return A pointer to the created Route
*/
Route *routeInitFromCities(City **cities, int numberOfCities);
/**
* Calculates the total distance of the Route. The result is stored in the route->distance
* @param route The route to calculate the distance for.
*/
void calcDistance(Route *route);
/**
* Prints the id for each city, as well as the total distance to the console
* @param route The Route to print
*/
void printRoute(Route *route);
/**
* Frees the Route and all of its cities if they have not been freed yet.
* @param route The Route to free
*/
void freeRoute(Route *route);


#endif