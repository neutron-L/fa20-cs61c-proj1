/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color * res = (Color *)malloc(sizeof(Color));
	unsigned int count = 0;

	// count the alive neighbors
	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
			if (!(i == 0 && j == 0) && 
			image->image[(row + i + image->rows) % image->rows][(col + j + image->cols) % image->cols].B & 1)
				++count;

	if (image->image[row][col].B & 1)
		count += 9;
	if ((1<<count) & rule) 
		res->R = res->G = res->B = 255;
	else
		res->R = res->G = res->B = 0;
	return res;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image * res = (Image *)malloc(sizeof(Image));
	res->rows = image->rows;
	res->cols = image->cols;
	res->image = (Color **)malloc(res->rows * sizeof(Color *));

	for (unsigned int i = 0; i < image->rows; ++i)
	{
		res->image[i] = (Color *)malloc(res->cols * sizeof(Color));
		for (unsigned int j = 0; j < image->cols; ++j)
		{
			Color * pixel = evaluateOneCell(image, i, j, rule);
			res->image[i][j] = *pixel;
			free(pixel);
		}
	}

	return res;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3)
	{
		fprintf(stderr, "usage: ./gameOfLife filename rule\n");
		fprintf(stderr, "filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		fprintf(stderr, "rule is a hex number beginning with 0x; Life is 0x1808.\n");
		exit(-1);
	}
	uint32_t rule = strtol(argv[2], NULL, 16);
	Image *image = readData(argv[1]);
	if (image == NULL)
	{
		fprintf(stderr, "read data error\n");
		exit(-1);
	}
	Image * res = life(image, rule);	
	writeData(res);
	freeImage(image);
	freeImage(res);

	return 0;
}
