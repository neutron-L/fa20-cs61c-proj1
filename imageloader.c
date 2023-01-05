/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE * fp = fopen(filename, "r");
	Image * pi = NULL; 
	if (fp != NULL)
	{
		char buf[3];
		pi = (Image *)malloc(sizeof(Image));

		fscanf(fp, "%s", buf); // read P3
		fscanf(fp, "%d %d", &pi->cols, &pi->rows);
		fscanf(fp, "%s", buf);

		// allocate color matrix
		pi->image = (Color **)malloc(pi->rows * sizeof(Color *));
		for (unsigned int i = 0; i < pi->rows; ++i)
		{
			pi->image[i] = (Color *)malloc(pi->cols * sizeof(Color));
			for (unsigned int j = 0; j < pi->cols; ++j)
			{
				if (fscanf(fp, "%hhd %hhd %hhd", &pi->image[i][j].R, 
					&pi->image[i][j].G, &pi->image[i][j].B) != 3)
				{
					fprintf(stderr, "file %s is not valid\n", filename);
					return NULL;
				}
			}
		}
		fclose(fp);
	}
	else
		fprintf(stderr, "fail to open file %s\n", filename);

	return pi;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n%d %d\n255\n", image->cols, image->rows);

	for (unsigned int i = 0; i < image->rows; ++i)
	{
		for (unsigned int j = 0; j < image->cols; ++j)
		{
			if (j)
				printf("   ");
			printf("%3d %3d %3d", image->image[i][j].R, 
				image->image[i][j].G, image->image[i][j].B);
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for (unsigned int i = 0; i < image->rows; ++i)
		free(image->image[i]);
	free(image->image);
	free(image);
}