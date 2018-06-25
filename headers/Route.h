#ifndef ROUTE_H
#define ROUTE_H
#include "City.h"

typedef struct Route_t {
	City *cities;
	int numberOfCities;
	double distance;
}Route;

Route *init(int num);
Route *initFromCities(City *cities);
double calcDistance();

#endif