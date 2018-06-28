#ifndef SALESMAN_H
#define SALESMAN_H
#include "Route.h"
/**
* A Salesman object which keeps track of the best and worst routes, as well as the starting route, which is modified during runtime
*/
typedef struct Salesman_t {
	Route *startingRoute;
	Route *bestRoute;
	Route *worstRoute;
}Salesman;
/**
* Initializes the Salesman, and all of its Routes based on the given number of cities
* @param num The number of cities
*/
void init(int num);
/**
* Starts the process of finding the best and worst routes through exhaustive search. Returns the number of seconds that were taken for this process
* @return The total number of seconds taken evaluate every permutation of the route
*/
double compute();
/**
* Evaluates a single route by comparing it against both the best and worst routes
* @param route A pointer to the route being evaluated
*/
void evaluateRoute(Route *route);
/**
* Frees the memory used by the Salesman and all of the routes and cities
*/
void freeSalesman();

#endif