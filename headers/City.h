#ifndef CITY_H
#define CITY_H

typedef struct City_t {
	double x;
	double y;
	char id;
}City;

double distanceBetween(City *a, City *b);
City *cityInit(double x, double y, char id);
#endif