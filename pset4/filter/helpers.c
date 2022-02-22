#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate the average of the three rgb values
            int average = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen) / 3);
            //put the average into every one of the rgb values to get a grayscale
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //getting the sepia values
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //in case the values exceed 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // putting the new values in the rgb
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // first i wanna copy all the pixels into a separate array to lock the pixel values in place
    // if i dont do that and try to take the new value from image array itself it wont work coz the old rgb values i want to access would be gone alr
    // think about it like u can have a double sided arrow in c, only single sided, so instead, u make a triangle
    RGBTRIPLE proto[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            proto[i][j].rgbtRed = image[i][j].rgbtRed;
            proto[i][j].rgbtBlue = image[i][j].rgbtBlue;
            proto[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // make use of the width length to do this. since always the jth element + reflected jth element = width -1
            image[i][j].rgbtRed = proto[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtBlue = proto[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = proto[i][width - 1 - j].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //copy all the image pixel rgb values to a new array called proto
    RGBTRIPLE proto[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            proto[i][j].rgbtRed = image[i][j].rgbtRed;
            proto[i][j].rgbtBlue = image[i][j].rgbtBlue;
            proto[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redsum = 0;
            int greensum = 0;
            int bluesum = 0;
            
            // if at the top row
            if (i == 0)
            {
                for (int a = 0; a < 2; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        redsum = redsum + proto[i + a][j + b].rgbtRed;
                        greensum = greensum + proto[i + a][j + b].rgbtGreen;
                        bluesum = bluesum + proto[i + a][j + b].rgbtBlue;
                    }
                }

            }
            
            // if at the bottom row
            else if (i == height - 1)
            {
                for (int a = -1; a < 1; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        redsum = redsum + proto[i + a][j + b].rgbtRed;
                        greensum = greensum + proto[i + a][j + b].rgbtGreen;
                        bluesum = bluesum + proto[i + a][j + b].rgbtBlue;
                    }
                }

            }
            
            // if at the first column
            if (j == 0)
            {
                for (int a = -1; a < 2; a++)
                {
                    for (int b = 0; b < 2; b++)
                    {
                        redsum = redsum + proto[i + a][j + b].rgbtRed;
                        greensum = greensum + proto[i + a][j + b].rgbtGreen;
                        bluesum = bluesum + proto[i + a][j + b].rgbtBlue;
                    }
                }

            }
            
            // if at the last column
            else if (j == width - 1)
            {
                for (int a = -1; a < 2; a++)
                {
                    for (int b = -1; b < 1; b++)
                    {
                        redsum = redsum + proto[i + a][j + b].rgbtRed;
                        greensum = greensum + proto[i + a][j + b].rgbtGreen;
                        bluesum = bluesum + proto[i + a][j + b].rgbtBlue;
                    }
                }

            }
            
            // if in the middle
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                
                // goes through every pixel in the column before and after and then the row before and after, putting in their values as a sum of all of it 
                for (int a = -1; a < 2; a++)
                {
                    for (int b = -1; b < 2; b++)
                    {
                        redsum = redsum + proto[i + a][j + b].rgbtRed;
                        greensum = greensum + proto[i + a][j + b].rgbtGreen;
                        bluesum = bluesum + proto[i + a][j + b].rgbtBlue;
                    }
                }
            }


            // finding the average
            int averagered = round((float) redsum / 9);
            int averagegreen = round((float)greensum / 9);
            int averageblue = round((float)bluesum / 9);

            // putting in the new values 
            image[i][j].rgbtRed = averagered;
            image[i][j].rgbtBlue = averageblue;
            image[i][j].rgbtGreen = averagegreen;

        }
    }
    return;
}
