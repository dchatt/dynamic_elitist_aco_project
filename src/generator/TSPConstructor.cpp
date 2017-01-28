//TSP constructor

#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>

#include "TSPConstructor.h"

struct cityType{
	int x,y;
}cities[MAX_CITIES];

using namespace std;

int main(int argc, char *argv[])
{

    ofstream f1;
    f1.open(argv[1]);
    srand(time(NULL));
    
    
    int city;
    
    for(city =0 ;city<MAX_CITIES; city++)
    {
        cities[city].x = rand()%MAX_DIST;
		
    	cities[city].y = rand()%MAX_DIST;
    
        f1<<cities[city].x<<" "<<cities[city].y<<" "<<std::endl;
    }

    f1.close();

    return 0;

}
