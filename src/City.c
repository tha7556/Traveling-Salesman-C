#include "../headers/City.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/**
* Initializes the City
* Dynamically allocates the City, so it will need to be freed later
* @param x The city's x coordinate
* @param y The city's y coordinate
* @param id The id of the city
* @Return A pointer to the newly created City 
*/
City *cityInit(double x, double y, char id) {
	City *city = (City*)calloc(sizeof(City),1);
	city->x = x;
	city->y = y;
	city->id = id;
	return city;
}

/**
* Calculates the distance between 2 cities
* @param a A pointer to the first city
* @param b A pointer to the second city
* @return The distance between the 2 cities
*/
double distanceBetween(City *a, City *b) {
	return sqrt(pow(a->x-b->x,2) + pow(a->y-b->y,2));
}