/*
 * main.c
 *
 *  Created on: Nov 16, 2015
 */

#include <sys/types.h>
#include <sys/stat.h>
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
	struct stat fileStat;
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
	

	// Define arrays that hold filename and filesize information
	int **size = NULL;
	char **items = NULL;
	
	// Open the directory from the input
    	dir = opendir(path);

	
	//if directory is valid
  	  if(dir != NULL){
	
		while(ep = readdir(dir)){
			if(strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0){
				continue;
			}
			
			// Concatenate file path for the file in the loop
			strcpy(filePath, path);
			strcat(filePath, "/");
			strcat(filePath, ep->d_name);
		
			stat(filePath, &fileStat);
			//printf("%d\n", fileStat.st_size);
			sz = fileStat.st_size;
			
			// allocate memory for the filesize array
			size = (int**) realloc(size, sizeof(int*) * (i+1)); //allocate memory for entire array
			size[i] = (int*) realloc(size[i], sz); // allocate memory for each int
			
			//set each value
			size[i] = sz;
		
			items = (char**) realloc(items, sizeof(char*) * (i+1)); //allocate memory for entire array
			items[i] = (char*) realloc(items[i], strlen(ep->d_name)); // allocate memory for each string 
			
			// Copy the file name to the string array
			strcpy(items[i], ep->d_name);
			i++;
		}
		
		// Sort the two arrays
		qsort(items, i, (sizeof(items[0])), cmpchar);
		qsort(size, i, (sizeof(size[0])), cmpint);

		// Print the two sorted arrays to a text file.
		for(n = 0; n < i; n++){
			fprintf(textFile, "%s\n", items[n]);
			fprintf(sizeFile, "%d\n", size[n]);
		}
		
		// close the directory and files.
       	(void) closedir(dir);
		fclose(textFile);
		fclose(sizeFile);
		
		//Print success!
		printf("Output: size_listing.txt & alpha_listing.txt\n");
   	}
    else{ 
	perror("Cannot open directory \n");
	}
	
	
	return 0;
}


