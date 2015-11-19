/*
 * main.c
 *
 *  Created on: Nov 16, 2015
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	if( argc > 2 ){
      printf("Too many arguments supplied.\n");
    }
    else{
      printf("One argument expected.\n");
    }
	

	if (ENOENT == errno) {
		printf("Invalid Directory");
	} 
	else{
		printf("passed");
	}
	
}