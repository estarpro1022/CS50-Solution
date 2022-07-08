#include "helpers.h"
#include <math.h>

void average(int height, int width, RGBTRIPLE new_image[height + 2][width + 2], RGBTRIPLE image[height][width], int i, int j, int divisor);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int average_color = (int) round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average_color;
            image[i][j].rgbtGreen = average_color;
            image[i][j].rgbtRed = average_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Duplicate
    RGBTRIPLE old_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            old_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = old_image[i][width - j - 1];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || j == 0 || i == height + 1 || j == width + 1)
            {
                new_image[i][j].rgbtBlue = 0;
                new_image[i][j].rgbtGreen = 0;
                new_image[i][j].rgbtRed = 0;
            }
            else
            {
                new_image[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
                new_image[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                new_image[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i == 0 && j == 0) || (i == 0 && j == width - 1) || (i == height - 1 && j == 0) || (i == height - 1 && j == width - 1))
            {
                average(height, width, new_image, image, i, j, 4);
            }
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                average(height, width, new_image, image, i, j, 6);
            }
            else
            {
                average(height, width, new_image, image, i, j, 9);
            }
        }
    }
    return;
}

void average(int height, int width, RGBTRIPLE new_image[height + 2][width + 2], RGBTRIPLE image[height][width], int i, int j, int divisor)
{
    int sum_Blue = 0;
    int sum_Green = 0;
    int sum_Red = 0;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            sum_Blue += new_image[i + 1 + x][j + 1 + y].rgbtBlue;
            sum_Green += new_image[i + 1 + x][j + 1 + y].rgbtGreen;
            sum_Red += new_image[i + 1 + x][j + 1 + y].rgbtRed;
        }
    }

    image[i][j].rgbtBlue = (int) round(sum_Blue * 1.0 / divisor);
    image[i][j].rgbtGreen = (int) round(sum_Green * 1.0 / divisor);
    image[i][j].rgbtRed = (int) round(sum_Red * 1.0 / divisor);
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || j == 0 || i == height + 1 || j == width + 1)
            {
                new_image[i][j].rgbtBlue = 0;
                new_image[i][j].rgbtGreen = 0;
                new_image[i][j].rgbtRed = 0;
            }
            else
            {
                new_image[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
                new_image[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                new_image[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
            }
        }
    }

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            int Gx_Blue = 0;
            int Gy_Blue = 0;
            int Gx_Green = 0;
            int Gy_Green = 0;
            int Gx_Red = 0;
            int Gy_Red = 0;
            Gx_Blue += -new_image[i - 1][j - 1].rgbtBlue + new_image[i - 1][j + 1].rgbtBlue - 2 * new_image[i][j - 1].rgbtBlue + 2 * new_image[i][j + 1].rgbtBlue - new_image[i + 1][j - 1].rgbtBlue + new_image[i + 1][j + 1].rgbtBlue;
            Gy_Blue += -new_image[i - 1][j - 1].rgbtBlue - 2 * new_image[i - 1][j].rgbtBlue - new_image[i - 1][j + 1].rgbtBlue + new_image[i + 1][j - 1].rgbtBlue + 2 * new_image[i + 1][j].rgbtBlue + new_image[i + 1][j + 1].rgbtBlue;
            Gx_Green += -new_image[i - 1][j - 1].rgbtGreen + new_image[i - 1][j + 1].rgbtGreen - 2 * new_image[i][j - 1].rgbtGreen + 2 * new_image[i][j + 1].rgbtGreen - new_image[i + 1][j - 1].rgbtGreen + new_image[i + 1][j + 1].rgbtGreen;
            Gy_Green += -new_image[i - 1][j - 1].rgbtGreen - 2 * new_image[i - 1][j].rgbtGreen - new_image[i - 1][j + 1].rgbtGreen + new_image[i + 1][j - 1].rgbtGreen + 2 * new_image[i + 1][j].rgbtGreen + new_image[i + 1][j + 1].rgbtGreen;
            Gx_Red += -new_image[i - 1][j - 1].rgbtRed + new_image[i - 1][j + 1].rgbtRed - 2 * new_image[i][j - 1].rgbtRed + 2 * new_image[i][j + 1].rgbtRed - new_image[i + 1][j - 1].rgbtRed + new_image[i + 1][j + 1].rgbtRed;
            Gy_Red += -new_image[i - 1][j - 1].rgbtRed - 2 * new_image[i - 1][j].rgbtRed - new_image[i - 1][j + 1].rgbtRed + new_image[i + 1][j - 1].rgbtRed + 2 * new_image[i + 1][j].rgbtRed + new_image[i + 1][j + 1].rgbtRed;
            image[i - 1][j - 1].rgbtBlue = (255 >= (int) round(sqrt(Gx_Blue * Gx_Blue + Gy_Blue * Gy_Blue))) ? (int) round(sqrt(Gx_Blue * Gx_Blue + Gy_Blue * Gy_Blue)) : 255;
            image[i - 1][j - 1].rgbtGreen = (255 >= (int) round(sqrt(Gx_Green * Gx_Green + Gy_Green * Gy_Green))) ? (int) round(sqrt(Gx_Green * Gx_Green + Gy_Green * Gy_Green)) : 255;
            image[i - 1][j - 1].rgbtRed = (255 >= (int) round(sqrt(Gx_Red * Gx_Red + Gy_Red * Gy_Red))) ? (int) round(sqrt(Gx_Red * Gx_Red + Gy_Red * Gy_Red)) : 255;
        }
    }

    return;
}