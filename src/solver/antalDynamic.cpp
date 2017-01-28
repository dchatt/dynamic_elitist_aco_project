// Ant al - elitist systems
//Ant algorithms for Travelling salesman Problem

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <fstream>
//#include <cv.h>
//#include <highgui.h>

#include "parameter.h"

//#define MAX_CITIES 30
#define MAX_DIST 100
#define MAX_TOUR (MAX_CITIES * MAX_DIST)
//#define MAX_ANTS 30

using namespace std;

//Initial Definiton of the problem
struct cityType{
	int x,y;
};

struct antType{
	
	int curCity, nextCity, pathIndex;
	int tabu[MAX_CITIES];
	int path[MAX_CITIES];
	double tourLength;
};

//Ant algorithm problem parameters

#define ALPHA 1.0
#define BETA 5.0 //This parameter raises the weight of distance over pheromone
#define RHO 0.5 //Evapouration rate
#define QVAL 100
#define MAX_TOURS 20
#define MAX_TIME (MAX_TOURS * MAX_CITIES)
#define INIT_PHER (1.0/MAX_CITIES)
#define E_ACO 1.0
//#define PROB_ELITIST 0.5

//runtime Structures and global variables

cityType cities[MAX_CITIES];
antType ants[MAX_ANTS];

double dist[MAX_CITIES][MAX_CITIES];

double phero[MAX_CITIES][MAX_CITIES];

double best=(double)MAX_TOUR;
int bestIndex;

double first_sol_tourlen=(double)MAX_TOUR;

//function init() - initializes the entire graph

void init(char *cityfile)
{
	int from,to,ant;
    ifstream f1;
    
    f1.open(cityfile);
	
	//creating cities
	
	for(from = 0; from < MAX_CITIES; from++)
	{
		//randomly place cities
		/*
		cities[from].x = rand()%MAX_DIST;
		
		cities[from].y = rand()%MAX_DIST;
        */
        f1>>cities[from].x;
        f1>>cities[from].y;

        //cout<<cities[from].x<<" "<<cities[from].y<<endl;
		//printf("\n %d %d",cities[from].x, cities[from].y);
		for(to=0;to<MAX_CITIES;to++)
		{
			dist[from][to] = 0.0;
			phero[from][to] = INIT_PHER;
		}
	}
	
	//computing distance
	
	for(from = 0; from < MAX_CITIES; from++)
	{
		for( to =0; to < MAX_CITIES; to++)
		{
			if(to!=from && dist[from][to]==0.0)
			{
				int xd = pow( abs(cities[from].x - cities[to].x), 2);
				int yd = pow( abs(cities[from].y - cities[to].y), 2);
				
				dist[from][to] = sqrt(xd + yd);
				dist[to][from] = dist[from][to];
				
			}
		}
	}
	
	
	//initializing the ANTs
	
	to = 0;
	for( ant = 0; ant < MAX_ANTS; ant++)
	{
		if(to == MAX_CITIES)
			to=0;
		
		ants[ant].curCity = to++;
		
		for(from = 0; from < MAX_CITIES; from++)
		{
			ants[ant].tabu[from] = 0;
			ants[ant].path[from] = -1;
		}
		
		ants[ant].pathIndex = 1;
		ants[ant].path[0] = ants[ant].curCity;
		ants[ant].nextCity = -1;
		ants[ant].tourLength = 0;
		
		//loading first city into tabu list
		
		ants[ant].tabu[ants[ant].curCity] =1;
		
	}
}

//reinitialize all ants and redistribute them
void restartAnts()
{
	int ant,i,to=0;
	
	for(ant = 0; ant<MAX_ANTS; ant++)
	{
		if(ants[ant].tourLength < best)
		{
			best = ants[ant].tourLength;
			bestIndex = ant;
		}
		
		ants[ant].nextCity = -1;
		ants[ant].tourLength = 0.0;
		
		for(i=0;i<MAX_CITIES;i++)
		{
			ants[ant].tabu[i] = 0;
			ants[ant].path[i] = -1;
		}
		
		if(to == MAX_CITIES)
			to=0;
			
		ants[ant].curCity = to++;
		
		ants[ant].pathIndex = 1;
		ants[ant].path[0] = ants[ant].curCity;
		
		ants[ant].tabu[ants[ant].curCity] = 1;
	}
}

double antProduct(int from, int to)
{
   //cout << phero[from][to] << " " << dist[from][to] << endl;
	//cout << ( pow( phero[from][to], ALPHA) * pow( (1.0/ dist[from][to]), BETA)) << endl;
	return(( pow( phero[from][to], ALPHA) * pow( (1.0/ dist[from][to]), BETA))); 
}

int selectNextCity( int ant )
{
	int from, to;
	double denom = 0.0;
	int iter_count=0;
	
	from=ants[ant].curCity;
	
	for(to=0;to<MAX_CITIES;to++)
	{
		if(ants[ant].tabu[to] == 0)
		{
			denom += antProduct( from, to );
		}
	}
	
	assert(denom != 0.0);
	
	do
	{
		double p;
		to++;
		
		if(to >= MAX_CITIES)
			to=0;
		if(ants[ant].tabu[to] == 0)
		{
			p = antProduct(from,to)/denom;
			
			if(p==0) 
			{
				p=(double)0.5;
			}
			
			
			//printf("\n%lf %lf", (double)rand()/RAND_MAX,p);
			double x = ((double)rand()/RAND_MAX); 
			
			//cout << "x:" << x << " p:" << p << endl;
			assert(p != 0.0);
			if(x < p)
			{
				//printf("%lf %lf Yo!",p,x);
			   //cout << "hit" << endl;
				break;
			}
		}
		iter_count++;
		if(iter_count > 5*MAX_CITIES)
		{
			break;
		}
	}while(1);
	
	return to;
}
	
int simulateAnts()
{
	int k;
	int moving = 0;
	
	for(k=0; k<MAX_ANTS; k++)
	{
		//checking if there are any more cities to visit
		//cout << "came here iterating " << k << endl;
		
		if( ants[k].pathIndex < MAX_CITIES )
		{
			ants[k].nextCity = selectNextCity(k);
			ants[k].tabu[ants[k].nextCity] = 1;
			ants[k].path[ants[k].pathIndex++] = ants[k].nextCity;
			
			ants[k].tourLength += dist[ants[k].curCity][ants[k].nextCity];
			
			//handle last case->last city to first
			
			if(ants[k].pathIndex == MAX_CITIES)
			{
				ants[k].tourLength += dist[ants[k].path[MAX_CITIES -1]][ants[k].path[0]];
			}
			
			ants[k].curCity = ants[k].nextCity;
			moving++;
			
		}
	}
	
	return moving;
}

double getProbElitist(int scheme, int curTime)
{
	if(scheme==0)
	{
		return PROB_ELITIST;
	}
	if(scheme==1)
	{
		return (double)(best / (double) first_sol_tourlen);
	}
	if(scheme==2)
	{
		return (double)1.0 - (double)(best / (double) first_sol_tourlen);
	}
	if(scheme==3)
	{
		return (double) curTime / (double) MAX_TIME;
	}
	if(scheme==4)
	{
		return (double)1.0 - (double) curTime / (double) MAX_TIME;
	}
	return  0;
}

double getChanceElitist()
{
	return ((double)rand()/RAND_MAX);
}

//Updating trails

void updateTrails(int scheme, int curTime)
{
	int from,to,i,ant,flag = 0,k;
	double chanceElitist,probElitist;
	
	//Pheromone Evaporation
	
	for(from=0; from<MAX_CITIES;from++)
	{
		for(to=0;to<MAX_CITIES;to++)
		{
			if(from!=to)
			{
				phero[from][to] *=( 1.0 - RHO);
				
				if(phero[from][to]<0.0)
				{
					phero[from][to] = INIT_PHER;
				}
			}
		}
	}
	
	//Add new pheromone to the trails
	
	for(ant=0;ant<MAX_ANTS;ant++)
	{
		for(i=0;i<MAX_CITIES;i++)
		{	
			if( i < MAX_CITIES-1 )
			{
				from = ants[ant].path[i];
				to = ants[ant].path[i+1];
			}
			else
			{
				from = ants[ant].path[i];
				to = ants[ant].path[0];
			}
			for(k=0;k<MAX_CITIES;k++)
         {
                if(from == ants[bestIndex].path[k] && to==ants[bestIndex].path[k+1])
                    flag = 1;
         } 
         if(flag == 1)
         {
				 chanceElitist = getChanceElitist();
				 
				 probElitist = getProbElitist(scheme,curTime);
				 
				 if( chanceElitist < (double)probElitist )
				 {
			    		phero[from][to] += (QVAL/ ants[ant].tourLength) + (QVAL/ best ) ; //Elitist updation
			    		phero[to][from] = phero[from][to];
				 }
				 else
				 {
				 		phero[from][to] += (QVAL/ ants[ant].tourLength) ;
			    		phero[to][from] = phero[from][to];
				 }
			}
         else
         {
             phero[from][to] += (QVAL/ ants[ant].tourLength) ;
			    phero[to][from] = phero[from][to];
         }
		}
	}
	
	for (from=0; from < MAX_CITIES;from++)
	{
		for( to=0; to<MAX_CITIES; to++)
		{
			phero[from][to] *= RHO;
		}
	}
	
}


void emitDataFile(int bestIndex)
{
	ofstream f1;
	f1.open("Data_prob_elitist.txt");
	antType antBest;
	antBest = ants[bestIndex];
	//f1<<antBest.curCity<<" "<<antBest.tourLength<<"\n";
	int i;
	for(i=0;i<MAX_CITIES;i++)
	{
		f1<<antBest.path[i]<<" ";
	}
	
	f1.close();
	
	f1.open("city_data_prob_elitist.txt");
	for(i=0;i<MAX_CITIES;i++)
	{
		f1<<cities[i].x<<" "<<cities[i].y<<"\n";
	}
	f1.close();
	
}
	


int main(int argc, char *argv[])
{
    int curTime = 0;
	 
	 int prev_best = 1000000000;
	 int time_to_converge = 0;
	 
	 int scheme = 0;

	int iter_count=0;
	 
	if( argc  > 3)
	{
   	cout<<"ACO- Prob Elitist";
		cout<<"MaxTime="<<MAX_TIME;
	}
	
	srand(time(NULL));
	
	init(argv[1]);
	
	scheme = atoi(argv[2]);
	
	while( curTime++ < MAX_TIME)
	{
	   //cout << "came here:" << curTime << endl;
		if( simulateAnts() == 0)
		{

 
			updateTrails(scheme,curTime);
			//cout << "came here" << endl;
			
			if(curTime != MAX_TIME)
				restartAnts();

			if(iter_count==0)
			{
				first_sol_tourlen=best;
			}
            iter_count++;

			if( argc  > 3)
			{	
				cout<<"\n Time is "<<curTime<<"("<<best<<")";
			}
		}
		if( prev_best > best)
		{
			prev_best = best;
			time_to_converge = curTime;
		}	
	}
	
	if( argc > 3)
	{
		cout<<"\nACO- prob E: Best tour = "<<best << " Time to converge = " << time_to_converge <<endl<<endl<<endl;
	}	
	cout << best << "," << time_to_converge << endl;
	
	//emitDataFile(bestIndex);
	
	return 0;
}
	
				
	


		
			
	  
		
	 

 
