#ifndef CITY_H
#define CITY_H

/**
* A City object that holds its x and y coordinates, as well as a char id
*/
typedef struct City_t {
	double x;
	double y;
	char id;
}City;

/**
* Initializes the City
* @param x The city's x coordinate
* @param y The city's y coordinate
* @param id The id of the city
* @Return A pointer to the newly created City 
*/
City *cityInit(double x, double y, char id);

/**
* Calculates the distance between 2 cities
* @param a A pointer to the first city
* @param b A pointer to the second city
* @return The distance between the 2 cities
*/
double distanceBetween(City *a, City *b);

#endif