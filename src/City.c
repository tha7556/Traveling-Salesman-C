#include "../headers/City.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

City *cityInit(double x, double y, char id) {
	City *city = (City*)calloc(sizeof(City),1);
	city->x = x;
	city->y = y;
	city->id = id;
	return city;
}
double distanceBetween(City *a, City *b) {
	return (pow(a->x-b->x,2) + pow(a->y-b->y,2));
}