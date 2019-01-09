# MovieLab
C program modules for movie expanded from image filters in psuedo-Photoshop program. Project based on EECS22 (Advanced C programming) coursework.


Building onto the psuedo-Photoshop program that takes in an image input, applies a filter to the image, and outputs the modified image, this program converts the image into a movie. The movie can take in either an image or a movie as input and outputs a movie with the applied filter over time. The movie can be viewed using an additional software "Xming" running in the background.  

The movie conversion is built entirely upon data structures and pointers. Structures including the movie, movie frames, image list, and image entries were utilized to append or prepend images to the list over a set number of frames defined in the command lines at execution time. 

The desired function to be applied determines the direction of images appended to the image list. When played, each frame will contain a slightly modified image so that cohesively the images form a smooth movie through the use of insertion sort. Currently, this program supports the hue and saturation filters, as well as playing the movie in reverse. 

------------------------------------------------------------------------------------------------------------------------------------------
Individual file functions:
- DIPs files: contain the digital image processing functions (filters)
- FileIO : load and save images
- Image files: manage the color pixels of the images
- ImageList files: manage the image list structure by appending images to the flexible double-linked list
- IterativeFilter files: append the image to the image list and convert image to YUV movie format for each frame
- Makefile: compile all of the programs together, make an executable file to run program
- Movie files: manage the color pixels of the movie
- MovieIO files: load and save movie frames
- MovieLab file: main function that supports command line arguments, calls all other functions depending on input
