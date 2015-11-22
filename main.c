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

// Returns 1 if A > B, Returns -1 if A < B, returns 0 if equal
int cmpchar(const void *A, const void *B)
{
  const char *a=*(const char**)A;
  const char *b=*(const char**)B;
  return strcmp(a,b);
}

// Returns 1 if A > B, Returns -1 if A < B, returns 0 if equal
int cmpint (const void *a, const void *b) {
    if (*(int*)a > *(int*)b) return 1;
 	else if (*(int*)a < *(int*)b) return -1;
  	else return 0;  
}


int main( int argc, const char* argv[] )
{
	// Define Int Variables
	int i = 0;
	int n = 0;
	int x = 0;
	int sz = 0;
	
	// Define Directory
	struct dirent *ep;
	DIR *dir;
	
	char *filePath;
	char *path;
	
	// Get directory from user
	path = (char *)argv[1];

	// Allocate enough memory for string of full file paths.
	filePath = malloc(strlen(path)+255+1);
	strcpy(filePath, path);
	
	
	// Define output text files
	FILE *textFile = fopen("aplha_listing.txt", "w");
	FILE *sizeFile = fopen("size_listing.txt", "w");
	
	
	int **size = NULL;
	char **items = NULL;
	char **items2 = NULL;
	
    	dir = opendir(path);
	
	
    if(dir != NULL){
		while(ep = readdir(dir)){
			if(strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0){
				continue;
			}
			
			strcpy(filePath, path);
			strcat(filePath, "/");
			strcat(filePath, ep->d_name);
		
			
			FILE *specificFile = fopen(filePath, "r");
			fseek(specificFile, 0L, SEEK_END);
			sz = ftell(specificFile);
			fclose(specificFile);
			
			size = (int**) realloc(size, sizeof(int*) * (i+1));
			size[i] = (int*) realloc(size[i], sz);
			
			size[i] = sz;
		
			
			items = (char**) realloc(items, sizeof(char*) * (i+1)); //allocate memory for entire array
			items[i] = (char*) realloc(items[i], strlen(ep->d_name)); // allocate memory for each string 
			
			strcpy(items[i], ep->d_name);
			i++;
		}
		
		qsort(items, i, (sizeof(items[0])), cmpchar);
		qsort(size, i, (sizeof(size[0])), cmpint);

		for(n = 0; n < i; n++){
			fprintf(textFile, "%s\n", items[n]);
			fprintf(sizeFile, "%d\n", size[n]);
		}
		
       	(void) closedir(dir);
		fclose(textFile);
		fclose(sizeFile);
		printf("Output: size_listing.txt & alpha_listing.txt");
   	}
    else{ 
	perror("Cannot open directory \n");
	}
	
	
	return 0;
}


