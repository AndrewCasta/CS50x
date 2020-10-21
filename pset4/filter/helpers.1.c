#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //  take the average of the red, green, and blue values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int g = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
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
            int sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            // sepiaGreen
            int sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            // sepiaRed
            int sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
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
        // loop through width j, j < width / 2
        // (only swap one half with the other, not iterate over twice)
        // swap the positions
        // image at width j = temp version at [width - j]
        for (int j = 0; j < halfWidth; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = tmp;
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

    // nested loop i & j

    // if image[i][j] == special case, else mix pixel

    RGBTRIPLE blurImg[height][width];

    for (int i = 1; i < height; i++)
    {
        for (int j = 1; j < width; j++)
        {

            // top left corner case
            if (image[i][j] == image[0][0])
            {
                // red blur
                int blurRed =
                (image[i][j].rgbtRed +
                image[i][j + 1].rgbtRed +
                image[i + 1][j].rgbtRed +
                image[i + 1][j + 1].rgbtRed) / 4;

                blurImg[i][j].rgbtRed = blurRed;

                // green blur
                int blurGreen =
                (image[i][j].rgbtGreen +
                image[i][j + 1].rgbtGreen +
                image[i + 1][j].rgbtGreen +
                image[i + 1][j + 1].rgbtGreen) / 4;

                blurImg[i][j].rgbtGreen = blurGreen;

                // blue blur
                int blurBlue =
                (image[i][j].rgbtBlue +
                image[i][j + 1].rgbtBlue +
                image[i + 1][j].rgbtBlue +
                image[i + 1][j + 1].rgbtBlue) / 4;

                blurImg[i][j].rgbtBlue = blurBlue;
            }
            // top right corner case
            if (image[i][j] == image[0][width - 1])
            {

            }
            // bottom left corner case
            if (image[i][j] == image[heigh - 1][0])
            {

            }
            // bottom right corner case
            if (image[i][j] == image[heigh - 1][width - 1])
            {

            }
            // first line
            if (image[i][j] == image[0][j])
            {

            }
            // last line
            if (image[i][j] == image[heigh - 1][j])
            {

            }
            // left edge
            if (image[i][j] == image[i][0])
            {

            }
            // right edge
            if (image[i][j] == image[i][width - 1])
            {

            }


            // middle pixels
            else
            {
                // red blur
                int blurRed =
                (image[i - 1][j - 1].rgbtRed +
                image[i - 1][j].rgbtRed +
                image[i - 1][j + 1].rgbtRed +
                image[i][j - 1].rgbtRed +
                image[i][j].rgbtRed +
                image[i][j + 1].rgbtRed +
                image[i + 1][j - 1].rgbtRed +
                image[i + 1][j].rgbtRed +
                image[i + 1][j + 1].rgbtRed) / 9;

                blurImg[i][j].rgbtRed = blurRed;

                // green blur
                int blurGreen =
                (image[i - 1][j - 1].rgbtGreen +
                image[i - 1][j].rgbtGreen +
                image[i - 1][j + 1].rgbtGreen +
                image[i][j - 1].rgbtGreen +
                image[i][j].rgbtGreen +
                image[i][j + 1].rgbtGreen +
                image[i + 1][j - 1].rgbtGreen +
                image[i + 1][j].rgbtGreen +
                image[i + 1][j + 1].rgbtGreen) / 9;

                blurImg[i][j].rgbtGreen = blurGreen;

                // blue blur
                int blurBlue =
                (image[i - 1][j - 1].rgbtBlue +
                image[i - 1][j].rgbtBlue +
                image[i - 1][j + 1].rgbtBlue +
                image[i][j - 1].rgbtBlue +
                image[i][j].rgbtBlue +
                image[i][j + 1].rgbtBlue +
                image[i + 1][j - 1].rgbtBlue +
                image[i + 1][j].rgbtBlue +
                image[i + 1][j + 1].rgbtBlue) / 9;

                blurImg[i][j].rgbtBlue = blurBlue;
            }
        }
    }
    // after creating blurImg array, loop again and swap image values to blurImg image values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurImg[i][j];
        }
    }


    return;
}
