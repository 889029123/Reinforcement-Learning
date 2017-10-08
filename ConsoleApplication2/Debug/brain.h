#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265
#define DLLIMPORT __declspec(dllexport) 
extern "C"
{
	__declspec(dllexport) void calc_wp(int n, double mean[], double std[], double prob[]);
}