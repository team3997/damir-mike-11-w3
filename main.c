/*
 * main.c
 *
 *  Created on: Nov 16, 2015
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, const char* argv[] )
{
	int i = 0;
	struct dirent *ep;
	DIR *dir;

	char *path;
	path = (char *)argv[1];

	FILE *textFile = fopen("listing.txt", "w");
	


	
    	dir = opendir(path);
    	if(dir != NULL){
		while(ep = readdir(dir)){
       			puts(ep->d_name);	
			fprintf(textFile, "%s\n", ep->d_name);
		}
        	(void) closedir(dir);
		fclose(textFile);
    	}
    	else
    	{ 
		perror("Cannot open directory \n");
    	}
	return 0;
}
