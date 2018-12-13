/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"
#include "Image.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
	IENTRY *imageEntry = malloc(sizeof(IENTRY));//allocate memory for the image entry

	if (imageEntry == NULL)
	{
		perror("Error: imageEntry memory allocation failed!\n");
		free(imageEntry);
		exit(0);
	}
	
	imageEntry -> List = NULL; //initialize all of the image entries and their lists and images as null
	imageEntry -> Next = NULL;
	imageEntry -> Prev = NULL;
	imageEntry -> RGBImage = NULL;
	imageEntry -> YUVImage = NULL;	

	return imageEntry;
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
	assert(entry);

	//free image objects
	IMAGE *RGBImage = entry -> RGBImage;
	YUVIMAGE *YUVImage = entry -> YUVImage;

	if (entry -> RGBImage) //if the entry has an image, free the image from memory
	{
		DeleteImage(RGBImage);
	}
	if (entry -> YUVImage) 
	{
		DeleteYUVImage(YUVImage);
	}

	free(entry); //free the image entry that contains no images
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *imagelist = malloc(sizeof(ILIST)); //allocate memory for the imagelist

	if (imagelist == NULL)
	{ 
		perror("Error: imagelist memory allocation failed!\n");
		free(imagelist);
		exit(0);
	}

	imagelist -> First = NULL; //initialize the imagelist ends as null, and length as 0
	imagelist -> Last = NULL;
	imagelist -> length = 0;	

	return imagelist;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	assert(list);

	//free all of the possible entries
	IENTRY *currentEntry;
	currentEntry = list -> First; 
	IENTRY *next; //storage pointer
	if (currentEntry -> YUVImage != NULL) //if entry points to an image, delete entry
	{	
		while(currentEntry)
		{
			next = currentEntry -> Next;
			DeleteImageEntry(currentEntry);
			currentEntry = next; //go to the next entry, and set another storage pointer for the next one
		}
	}

	else if (currentEntry -> RGBImage != NULL) //repeat entry deletions for RGB images
	{
		while(currentEntry)
		{
			next = currentEntry -> Next;
			DeleteImageEntry(currentEntry);
			currentEntry = next;		
		}
	}	

	free(list);	//free the empty list
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	IENTRY *RGBEntry;
	RGBEntry = CreateImageEntry(); //create an image entry for the RGB image
	RGBEntry -> YUVImage = NULL; //ensure the YUV aspect of the RGB entry is empty
	RGBEntry -> RGBImage = RGBimage; //ensure the RGB aspect of the RGB entry is the RGB image
	RGBEntry -> List = list; //the List of the entry is equal to the list parameter passed in
	IENTRY *CurrentEntry = list -> Last;

	if (RGBEntry -> List -> Last == NULL) //append an image entry to the end of the list 
	{
		list -> First = RGBEntry;
		list -> Last = RGBEntry;
		RGBEntry -> Prev = NULL;
		RGBEntry -> Next = NULL;
	}
	
	else
	{
		RGBEntry -> Next = NULL;
		RGBEntry -> Prev = CurrentEntry;
		list -> Last = RGBEntry;
		CurrentEntry -> Next = RGBEntry;
	}
		list -> length++; //increase the length initialized as 0 by 1 for each image entry		
	
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	IENTRY *YUVEntry;
	YUVEntry  = CreateImageEntry(); //create an image entry for the YUV image
	YUVEntry -> YUVImage = YUVimage; //ensure the YUV aspect is the YUV image
	YUVEntry -> RGBImage = NULL;  //ensure the RGB aspect is empty
	IENTRY *CurrentEntry = list -> Last; 

	if (list -> Last == NULL) //append an image entry to the end of the list
	{
		list -> First = YUVEntry;
		list -> Last = YUVEntry;
		YUVEntry -> Prev = NULL;
		YUVEntry -> Next = NULL;
	}
	
	else
	{
		YUVEntry -> Next = NULL;
		YUVEntry -> Prev = CurrentEntry;
		list-> Last = YUVEntry;
		CurrentEntry -> Next = YUVEntry;
	}
		list -> length++; //increase the length initialized as 0 by 1 for each image entry
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	unsigned int newFrameNum = 0;
	unsigned int counter = 0;
	IENTRY *curr = NULL; /* current entry in the list */
	IENTRY *prev = NULL; /* previous kept entry in the list */
	IENTRY *next = NULL; /* next entry in the list */

	assert(list);
	assert(factor > 0);

	curr = list->First;

	while (curr != NULL) {
		next = curr->Next;

		if (counter % factor == 0) {
			newFrameNum ++;

			curr->Prev = prev;
			if (prev != NULL) {
				prev->Next = curr;
			}
			prev = curr;
		} else {
			if (curr->RGBImage != NULL) {
				DeleteImage(curr->RGBImage);
			}

			if (curr->YUVImage != NULL) {
				DeleteYUVImage(curr->YUVImage);
			}

			curr->List = NULL;
			curr->Next = NULL;
			curr->Prev = NULL;
			curr->RGBImage = NULL;
			curr->YUVImage = NULL;
			free(curr);
			}

		curr = next;
		counter ++;
	}

	list->Last = prev;
	if (prev != NULL) {
		prev->Next = NULL;
	}
	list->length = newFrameNum;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	IENTRY *tmp = NULL; //initialize 2 storage pointers
	IENTRY *current = NULL;
	current = list -> First; //start with pointer current to the first element of the image list
	
	while(current != NULL)
	{
		tmp = current -> Next; //set tmp to the next element
		current -> Next = current -> Prev;	//set next element to previous element
		current -> Prev = tmp;  //swap the previous element to next element (stored in pointer tmp)
		current = current -> Prev; //set the current to the previous element (which is now the next element)
	}

	tmp = list -> First; //reverse the image list
	list -> First = list -> Last;
	list -> Last = tmp;	
}

/* EOF */
