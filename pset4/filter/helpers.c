#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int x = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3);
            image[i][j].rgbtBlue = x;
            image[i][j].rgbtGreen = x;
            image[i][j].rgbtRed = x;
            
        }    
    }
    return;
}
/*Sepia
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int sepiaRed = round((0.393*image[i][j].rgbtBlue + 0.769*image[i][j].rgbtGreen + 0.189*image[i][j].rgbtRed));
            int sepiaGreen = round((0.349*image[i][j].rgbtBlue + 0.686*image[i][j].rgbtGreen + 0.168*image[i][j].rgbtRed));
            int sepiaBlue = round((0.272*image[i][j].rgbtBlue + 0.534*image[i][j].rgbtGreen + 0.131*image[i][j].rgbtRed));
            
            if(sepiaRed > 255){
                sepiaRed = 255;
            }
            if(sepiaGreen > 255){
                sepiaGreen = 255;
            }
             if(sepiaBlue > 255){
                sepiaBlue = 255;
            }
            
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
            
        }    
    }*/
    
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < (width/2); j++){
            
            int tmpBlue = image[i][j].rgbtBlue;
            int tmpGreen = image[i][j].rgbtGreen;
            int tmpRed = image[i][j].rgbtRed;
            
    
            image[i][j].rgbtBlue = image[i][(width - 1)-j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][(width - 1)-j].rgbtGreen;
            image[i][j].rgbtRed = image[i][(width - 1)-j].rgbtRed;
            
            image[i][(width - 1)-j].rgbtBlue = tmpBlue;
            image[i][(width - 1)-j].rgbtGreen = tmpGreen;
            image[i][(width - 1)-j].rgbtRed = tmpRed; 

            
        }    
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int mediaRed = 0;
    int mediaGreen = 0;
    int mediaBlue = 0;
    int cont = 0;
    RGBTRIPLE temp[height][width];

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            
            for(int x = i - 1; x < i + 2; x++){
                if (x - 1 < 0){
                    x++;
                }
                if (x + 1 > height){
                    break;
                }
                for(int y = j - 1; y < j + 2; y++){  
                    if (y - 1 < 0){
                        y++;
                    }
                    if (y + 1 > width){
                        break;
                    }   
                    mediaRed += image[x][y].rgbtRed;
                    mediaGreen += image[x][y].rgbtGreen;
                    mediaBlue += image[x][y].rgbtBlue;
                    cont++;
                    
                }
            }
            temp[i][j].rgbtRed = round(mediaRed / cont);
            temp[i][j].rgbtGreen = round(mediaGreen / cont);
            temp[i][j].rgbtBlue = round(mediaBlue / cont);

            mediaRed = 0;
            mediaGreen = 0;
            mediaBlue = 0;    
            cont = 0;
            
        }    
    }    
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }

    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float GxRed = 0;
    float GxGreen = 0;
    float GxBlue = 0;
    float GyRed = 0;
    float GyGreen = 0;
    float GyBlue = 0;
    
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            GxRed = 0;
            GxGreen = 0;
            GxBlue = 0;
            GyRed = 0;
            GyGreen = 0;
            GyBlue = 0; 
            for(int x = - 1; x < 2; x++){
                for(int y = - 1; y < 2; y++){
                    if (i + x < 0 || i + x >= height)
                    {
                        continue;
                    }
                    if (j + y < 0 || j + y >= width)
                    {
                        continue;
                    }
                    GxRed += (temp[i+x][j+y].rgbtRed * Gx[x + 1][y + 1]);
                    GxGreen += (temp[i+x][j+y].rgbtGreen * Gx[x + 1][y + 1]);
                    GxBlue += (temp[i+x][j+y].rgbtBlue * Gx[x + 1][y + 1]);
                    GyRed += (temp[i+x][j+y].rgbtRed * Gy[x + 1][y + 1]);
                    GyGreen += (temp[i+x][j+y].rgbtGreen * Gy[x + 1][y + 1]);
                    GyBlue += (temp[i+x][j+y].rgbtBlue * Gy[x + 1][y + 1]);                        

                }
            }
            
            int rgbtRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int rgbtGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int rgbtBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            
            if (rgbtRed  > 255)
            {
                rgbtRed  = 255;
            }
            if (rgbtGreen > 255)
            {
                rgbtGreen = 255;
            }
            if (rgbtBlue > 255)
            {
                rgbtBlue = 255;
            }

            image[i][j].rgbtRed = rgbtRed;
            image[i][j].rgbtGreen = rgbtGreen;
            image[i][j].rgbtBlue = rgbtBlue;
        }    
    }    
    
    return;
}
