/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

int clip(int a) //function for checking values between 0 and 255
{
	if (a < 0)
	{
		a = 0;
	}

	else if (a > 255)
	{
		a = 255;
	}

	return a; 
}

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	MOVIE *movie = malloc(sizeof(MOVIE)); //allocate memory for the movie
	
	if (movie == NULL)
	{
		perror("Error: movie memory allocation failed!\n");
		free(movie);
		exit(0);
	}

	movie -> Frames = CreateImageList(); //make an image list Frames
	return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	DeleteImageList(movie -> Frames); //free the image list
	free(movie); //free the movie
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	assert(movie);
	IENTRY *tmp; //initialize 2 storage pointers
	IENTRY *next;

	tmp = movie -> Frames -> First; //start at the first element of the Frames list
	int x, y, z;
	int C, D, E;
	for (z = 0; z < MovieLength(movie); z++)
	{
		tmp -> RGBImage = CreateImage(MovieWidth(movie), MovieHeight(movie)); //create an RGB image of passed dimensions for each frame
		next = tmp -> Next; //store the next image entry in 'next'

		for (x = 0; x < MovieWidth(movie); x++)
		{
			for (y = 0; y < MovieHeight(movie); y++) //conversion from YUV to RGB
			{	
				C = GetPixelY(tmp -> YUVImage, x, y) - 16;
				D = GetPixelU(tmp -> YUVImage, x, y) - 128;
				E = GetPixelV(tmp -> YUVImage, x, y) - 128;

				SetPixelR(tmp -> RGBImage, x, y, clip((298*C+409*E+128) >> 8)); //check within 0-255
				SetPixelG(tmp -> RGBImage, x, y, clip((298*C-100*D-208*E+128) >> 8));
				SetPixelB(tmp -> RGBImage, x, y, clip((298*C+516*D+128) >> 8));
			}
		}
		tmp -> YUVImage = NULL; //empty the YUV image after values are extracted and go to the next image entry stored in 'next'
		tmp = next;
	}
	
	free(tmp);
	free(next);
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	assert(movie);
	IENTRY *tmp; //initialize 2 storage pointers
	IENTRY *next;
	tmp = movie -> Frames -> First; //start at the first element of the Frames list

	int x, y, z;
	int R, G, B;

	for (z = 0; z < MovieLength(movie); z++)
	{
		tmp -> YUVImage = CreateYUVImage(MovieWidth(movie), MovieHeight(movie)); //create a YUV image for each frame
		next = tmp -> Next; //store the next image entry in pointer 'next'
		for (x = 0; x < MovieWidth(movie); x++)
		{
			for (y = 0; y < MovieHeight(movie); y++)
			{
				R = GetPixelR(tmp -> RGBImage, x, y); // convert RGB to YUV values
				G = GetPixelG(tmp -> RGBImage, x, y);
				B = GetPixelB(tmp -> RGBImage, x, y); 
				
				SetPixelY(tmp -> YUVImage, x, y, clip(((66*R+129*G+25*B+128) >> 8) + 16));
				SetPixelU(tmp -> YUVImage, x, y, clip(((-38*R-74*G+112*B+128) >> 8) + 128));
				SetPixelV(tmp -> YUVImage, x, y, clip(((112*R-94*G-18*B+128) >> 8) + 128));		
			}
		}
		tmp -> RGBImage = NULL; //empty the RGB image after values are extracted, go to next image entry in 'next'
		tmp = next;
	}

	free(tmp);
	free(next);
}

int MovieLength(const MOVIE *movie) //get the movie length
{
	assert(movie);
	return movie -> Frames -> length;	
}

int MovieHeight(const MOVIE *movie) //get the movie height from either RGB or YUV image
{
	assert(movie);

	if (movie -> Frames -> First -> RGBImage)
	{
		return movie -> Frames -> First -> RGBImage -> H; 
	}

	else
	{
		return movie -> Frames -> First -> YUVImage -> H;
	} 
}

int MovieWidth(const MOVIE *movie) //get the movie width from either RGB or YUV image
{
	assert(movie);
	
	if (movie -> Frames -> First -> RGBImage)
	{
		return movie -> Frames -> First -> RGBImage -> W;
	}

	else
	{
		return movie -> Frames -> First -> YUVImage -> W;
	}
}

/* EOF */
