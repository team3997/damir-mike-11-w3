/*
 * main.c
 *
 *  Created on: Nov 16, 2015
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main( int argc, const char* argv[] )
{
	int i = 0;
	int n = 0;
	struct dirent *ep;
	DIR *dir;

	char *path;
	path = (char *)argv[1];

	FILE *textFile = fopen("listing.txt", "w");
	
	char **items = NULL;
	
    	dir = opendir(path);
    	if(dir != NULL){
		while(ep = readdir(dir)){
			if(strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
				continue;
			printf("%s\n", ep->d_name);
			items = (char**) realloc(items, sizeof(char*) * (i+1));
			items[i] = (char*) realloc(items[i], strlen(ep->d_name));
			strcpy(items[i], ep->d_name);
			i++;
		}

		for(n = 0; n < i; n++){
			fprintf(textFile, "%s\n", items[n]);
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
