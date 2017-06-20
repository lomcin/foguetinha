#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
using namespace std;

//float precisao = 0.001;

#define linhas "\n\n\n\n"
#define copyPointsTo(_a,_metodo) (std::copy(_metodo::points.begin(),_metodo::points.end(), std::back_inserter(points[_a])))

//#define USE_OPENCV

#ifdef USE_OPENCV
	#include <opencv2/core.hpp>
	#include <opencv2/highgui.hpp>
	#include <opencv2/imgproc.hpp>
#endif

