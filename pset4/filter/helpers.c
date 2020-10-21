#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //  take the average of the red, green, and blue values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int g = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = g;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtRed = g;
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
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            // sepiaBlue
            int sepiaBlue = round((float)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            // sepiaGreen
            int sepiaGreen = round((float)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            // sepiaRed
            int sepiaRed = round((float)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // width is known
    // loop through height i
    int halfWidth = width / 2;
    for (int i = 0; i < height; i++)
    {
        // loop through width j, j < halfWidth
        // swap the positions
        for (int j = 0; j < halfWidth; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1  - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through all cells
    // special case for start & end rows, and corners
    // copy new values to output to avoid copying over bmp blurring based on new values

    // create new 2d array with final values stored
    RGBTRIPLE blurImg[height][width];

    // nested loop i & j
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // now I'm at image[i][j]
            // then another nested loop to check the surrounding boxes & add values if we good

            //set color stores & counter to 0.
            int blurRed = 0;
            int blurGreen = 0;
            int blurBlue = 0;
            int count = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // check all conditions of i & j using x & y, add when not -1 or width or height
                    if (j + x > -1 && j + x < width && i + y > -1 && i + y < height)
                    {
                        blurRed += image[i + y][j + x].rgbtRed;
                        blurGreen += image[i + y][j + x].rgbtGreen;
                        blurBlue += image[i + y][j + x].rgbtBlue;
                        count++;
                    }
                }
            }
            // set the new array based on the avg values
            blurImg[i][j].rgbtRed = round((float)blurRed / count);
            blurImg[i][j].rgbtGreen = round((float)blurGreen / count);
            blurImg[i][j].rgbtBlue = round((float)blurBlue / count);
        }
    }
    // after creating blurImg array, loop again and insert final blur image values into original image values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurImg[i][j];
        }
    }

    return;
}
