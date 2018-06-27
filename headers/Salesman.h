#ifndef SALESMAN_H
#define SALESMAN_H
#include "Route.h"

typedef struct Salesman_t {
	Route *startingRoute;
	Route *bestRoute;
	double bestFitness;
}Salesman;
void init(int num);
double compute();
void evaluateRoute(Route *route);
//Frees the salesman's routes
void freeSalesman();

#endif