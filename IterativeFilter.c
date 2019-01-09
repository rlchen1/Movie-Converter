#include "IterativeFilter.h"
#include "Movie.h"
#include <assert.h>

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, float start, float end, float change)
{
	assert(image);
	IMAGE *tmp = image; //create a pointer for the image for temporary storage
	MOVIE *movie = CreateMovie(); 

	while (start < end) // if going normal direction
	{
		{	
			tmp = CopyImage(image);
			tmp = filter(tmp, start); //apply the filter using passed parameters
			AppendRGBImage(movie->Frames,tmp); //append the modified image to the list

			start = start + change; 
		}
	}

	while (start > end) //if going reverse direction
	{
		{
			tmp = CopyImage(image);
			tmp = filter(tmp, start); //apply the filter using passed parameters
			AppendRGBImage(movie->Frames,tmp); //append the modified image to the list
	
			start = start - change;
		}
	}

	RGB2YUVMovie(movie); //convert the RGB values to YUV values in the movie
	return movie; 
}
