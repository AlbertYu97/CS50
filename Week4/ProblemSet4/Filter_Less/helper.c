#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            float average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;
            int averageInt = round(average);
            image[i][j].rgbtRed = averageInt;
            image[i][j].rgbtBlue = averageInt;
            image[i][j].rgbtGreen = averageInt;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Check if the value is greater than 255
            int red = (sepiaRed < 255) ? sepiaRed : 255;
            int green = (sepiaGreen < 255) ? sepiaGreen : 255;
            int blue = (sepiaBlue < 255) ? sepiaBlue : 255;

            //Set value
            image[i][j].rgbtRed = red;
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Switch pixels in the same row
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average the adajacent blocks
            float count = 0;
            int rgbtRed = 0;
            int rgbtGreen = 0;
            int rgbtBlue = 0;

            for (int y = i - 1; y <= i + 1; y++)
            {
                for (int x = j - 1; x <= j + 1; x++)
                {
                    if (y >= 0 && y <= height - 1 && x >= 0 && x <= width - 1)
                    {
                        count ++;
                        rgbtRed += copy[y][x].rgbtRed;
                        rgbtGreen += copy[y][x].rgbtGreen;
                        rgbtBlue += copy[y][x].rgbtBlue;
                    }
                }
            }
            // Update image
            int red = round(rgbtRed / count);
            int green = round(rgbtGreen / count);
            int blue = round(rgbtBlue / count);
            image[i][j].rgbtRed = red;
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
        }
    }
}
