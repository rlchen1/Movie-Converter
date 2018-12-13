/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/* Modified by Mihnea Chirila for EECS 22 Fall 2018                                                            */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

int main(int argc, char *argv[])
{
	int argnum = 1; //current argument number, start at 1 to exclude the executable name 
	int filter = 0; //check for hue (1), saturate (2), default (0)
	int direction = 0; //check for reverse (1), normal (0)
	unsigned int frameNum = 0;
	unsigned int width = 0, height = 0;
	float start, end, change;
	char *fnameImage = NULL; //store the name of loaded image
	char *fnameMovie = NULL; //store the name of loaded movie
	char *fnameOut = NULL;   //store the name of movie to export

	IMAGE *image = NULL;
	MOVIE *movie = NULL;

	iterableFilter hue = HueRotate; //argument hue calls function HueRotate
	iterableFilter saturation = Saturate; //argument saturation calls function Saturate

	while (argnum < argc)
	{
		if (strcmp(argv[argnum],"-i") == 0) //if argv is -i, value is true (0), import image
		{
			fnameImage = argv[argnum + 1];
			argnum = argnum + 2; 
			continue;			
		}
		
		if(strcmp(argv[argnum], "-m") == 0) //if argv is -m, import movie
		{
			fnameMovie = argv[argnum + 1];
			argnum = argnum + 2;
			continue;
		}
	
		if (strcmp(argv[argnum], "-o") == 0) //if argv is -o, export the movie
		{
			fnameOut = argv[argnum + 1];
			argnum = argnum + 2;
			continue;
		}
		
		if (strcmp(argv[argnum], "-f") == 0) //if argv is -f, set the number of frames
		{
			sscanf(argv[argnum+1], "%d", &frameNum);
			argnum = argnum + 2;
			continue;
		}

		if(strcmp(argv[argnum], "-s") == 0) //if argv is -s, set the movie width and height
		{
			sscanf(argv[argnum+1], "%dx%d", &width, &height);
			argnum = argnum + 2;	
			continue;
		}

		if (strcmp(argv[argnum], "-start=") == 0) //if argv is -start=, set start parameter
		{
			sscanf(argv[argnum+1], "%f", &start);
			argnum = argnum + 2;
			continue;
		}

		if (strcmp(argv[argnum], "-end=") == 0) //if argv is -end=, set end parameter
		{
			sscanf(argv[argnum+1], "%f", &end);
			argnum = argnum + 2;
			continue;
		}

		if (strcmp(argv[argnum], "-step=") == 0) //if argv is -step=, set step parameter
		{
			sscanf(argv[argnum+1], "%f", &change);
			argnum = argnum + 2;
			continue;
		}
		
		if (strcmp(argv[argnum], "-hue") == 0) //if argv is -hue, use hue filter
		{
			filter = 1;	
			argnum++;
			continue;
		}

		if (strcmp(argv[argnum], "-saturation") == 0) //if argv is -saturation, use saturation filter
		{
			filter = 2;	
			argnum++;
			continue;
		}
	
		if (strcmp(argv[argnum], "-reverse") == 0) //if argv is -reverse, do reverse function
		{
			direction = 1;
			argnum++;	
			continue;
		}
	}

	if (filter == 1) //if hue
	{
		image = LoadImage(fnameImage);
		movie = doIterativeFilter(image, hue, start, end, change);
		SaveMovie(fnameOut, movie);

		DeleteImage(image);
		DeleteMovie(movie);

		fnameImage = NULL;
		fnameMovie = NULL;
		fnameOut = NULL;
	}

	else if (filter == 2) //if saturation
	{
		image = LoadImage(fnameImage);
		movie = doIterativeFilter(image, saturation, start, end, change); //start, end are saturation percents(enter large numbers)
		SaveMovie(fnameOut, movie);

		DeleteImage(image);
		DeleteMovie(movie);

		fnameImage = NULL;
		fnameMovie = NULL;
		fnameOut = NULL;
	}

	if (direction == 1) //if reverse, load a movie
	{
		movie = LoadMovie(fnameMovie, frameNum, width, height);
		ReverseImageList(movie->Frames);
		SaveMovie(fnameOut, movie);

		if (image != NULL)
		{
			DeleteImage(image);
		}
		if (movie != NULL)
		{
			DeleteMovie(movie);
		}
	
		fnameImage = NULL;
		fnameMovie = NULL;
		fnameOut = NULL;
	}

	return 0;
}

/* EOF */
