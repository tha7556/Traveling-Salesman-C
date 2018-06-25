#ifndef SALESMAN_H
#define SALESMAN_H

typedef struct Salesman_t {
	Route *startingRoute;
	Route *bestRoute;
	double bestFitness;
}
void init();
double compute();
void evaluateRoute(Route *route);

#endif