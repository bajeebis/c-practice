#include "helpers.h"
#include <stdio.h>
#include <math.h>
#define ORD 9

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float x;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            x = (float)image[i][j].rgbtRed + (float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen;
            x /= 3;
            x = round(x);
            image[i][j].rgbtRed = (int)x;
            image[i][j].rgbtBlue = (int)x;
            image[i][j].rgbtGreen = (int)x;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        float r, g, b, red, green, blue;
        for (int j = 0; j < width; j++)
        {
            red = (float)image[i][j].rgbtRed;
            green = (float)image[i][j].rgbtGreen;
            blue = (float)image[i][j].rgbtBlue;
            r = round(0.393 * red + 0.769 * green + 0.189 * blue);
            g = round(0.349 * red + 0.686 * green + 0.168 * blue);
            b = round(0.272 * red + 0.534 * green + 0.131 * blue);

            //r = round(r);
            //g = round(g);
            //b = round(b);

            if (r > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = (int)r;
            }

            if (g > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = (int)g;
            }

            if (b > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = (int)b;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int x;
    float half;
    int red_ph;
    int blue_ph;
    int green_ph;

    //int test = width - 1;
    half = (float)(width - 1) / 2;
    half = (int)half;

    for (int i = 0; i < height; i++)
    {
        x = width - 1;
        for (int j = 0; j <= half; j++)
        {
            // Optimize this part8
            red_ph = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][x].rgbtRed;
            image[i][x].rgbtRed = red_ph;

            blue_ph = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][x].rgbtBlue;
            image[i][x].rgbtBlue = blue_ph;

            green_ph = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][x].rgbtGreen;
            image[i][x].rgbtGreen = green_ph;

            x -= 1;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int cval = 3;
    int arr[height][width][cval];

    // int ORD = 9;
    int box_x[ORD] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    int box_y[ORD] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};

    int temp_val, temp_x, temp_y;
    int r, g, b;
    for (int hc = 0; hc < height; hc++)
    {
        for (int wc = 0; wc < width; wc++)
        {
            float temp_r = 0, temp_g = 0, temp_b = 0;
            r = 0; // Counter
            for (int i = 0; i < ORD; i++)
            {
                temp_x = wc + box_x[i];
                temp_y = hc + box_y[i];
                if (temp_x < 0 || temp_x >= width || temp_y < 0 || temp_y >= height)
                {
                    continue;  // This inverted if check is better, remember
                }
                else
                {
                    temp_r += image[temp_y][temp_x].rgbtRed;
                    temp_g += image[temp_y][temp_x].rgbtGreen;
                    temp_b += image[temp_y][temp_x].rgbtBlue;

                    r += 1;
                }
            }
            temp_r = (float)temp_r / r;
            temp_g = (float)temp_g / r;
            temp_b = (float)temp_b / r;
            arr[hc][wc][0] = round(temp_r);
            arr[hc][wc][1] = round(temp_g);
            arr[hc][wc][2] = round(temp_b);
        }
    }

    for (int hc = 0; hc < height; hc++)
    {
        for (int wc = 0; wc < width; wc++)
        {
            image[hc][wc].rgbtRed = arr[hc][wc][0];
            image[hc][wc].rgbtGreen = arr[hc][wc][1];
            image[hc][wc].rgbtBlue = arr[hc][wc][2];
        }
    }
    return;
}