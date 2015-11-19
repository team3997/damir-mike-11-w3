/*
 * main.c
 *
 *  Created on: Nov 16, 2015
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
int main( int argc, const char* argv[] )
{
	int i = 0;
	struct dirent *ep;
	char *path;
	char *fileArray;
	path = (char *)argv[1];
	
    DIR *dir;

    dir = opendir(path);
	
    if(dir != NULL){
		i = 0;
		while(ep = readdir(dir)){
       		printf("%s\n", ep->d_name);
			
			fileArray[i] = ep->d_name;
			i++;
		}
        closedir(dir);
    }
    else
    { 
		perror("Cannot open directory \n");
    }
	return 0;
}