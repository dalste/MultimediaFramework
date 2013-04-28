//timer.cpp
/*
#include <iostream>
#include "timer.h"
#include <stdio.h>
using namespace std;


void main(void){
MyTimer timer;
int seconds = 0;
bool done = false;
float StartTime = timer.MyTimerGetTime();
float TimeElapsed;

	while (!done){

		if((TimeElapsed = timer.MyTimerGetTime() - StartTime) >= 1000){
			StartTime = timer.MyTimerGetTime();
		seconds++;
		cout << "time passed: " << seconds <<endl; 		
		if(seconds >= 60) done = true; 
		}

	}
}
*/