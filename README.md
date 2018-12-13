# MovieLab
C program modules for movie expanded from image filters in psuedo-Photoshop program

Building onto the psuedo-Photoshop program that takes in an image input, applies a filter to the image, and outputs the modified image, this program converts the image into a movie. The movie can take in either an image or a movie as input and outputs a movie with the applied filter over time. 

The movie conversion is built entirely upon data structures and pointers. Structures including the movie, movie frames, image list, and image entries were utilized to append or prepend images to the list over a set number of frames defined in the command lines at execution time. 

The desired function to be applied determines the direction of images appended to the image list. When played, each frame will contain a slightly modified image so that cohesively the images form a smooth movie through the use of insertion sort. Currently, this program supports the hue and saturation filters, as well as playing the movie in reverse. 
