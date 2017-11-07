//
//  main.cpp
//  IPproject_MichalGrzymski
//
//  Created by Michał Grzymski on 24/10/2017.
//  Copyright © 2017 Michal Grzymski. All rights reserved.
//

// Include librares: cstdlib for printf finction - an easy way to print text to he console by using C; I just prefert it over C++'s cout function.
#include <cstdlib>
// math.h - I use it for M_PI. this is a convinient way of including PI value in the calculations below.
#include <math.h>
// opencv2opencv/hpp - For using OpenCV functions, such as load and display an image.
#include <opencv2/opencv.hpp>

// Use both standtard and OpenCV namespaces.
using namespace std;
using namespace cv;

// Main function is initilized.
int main()
{
    
    // Created a matrix of pixels from an image that is being lodead by finction imread.
    Mat source = imread("/Users/MichalGrzymski/Downloads/bmp.png");
    
    // Create 4 additional matrixes of pixels, one for each H-, S-, I- and HSI image.
    Mat hImage(source.rows, source.cols, source.type());
    Mat sImage(source.rows, source.cols, source.type());
    Mat iImage(source.rows, source.cols, source.type());
    Mat HSI(source.rows, source.cols, source.type());
   
    // Initialise variables that will be used in the algorythm below. R, G and B are used for transforming colourspace to HSI.
    // Variable H has to have assaigned value - otherwise XCode will display an error...
    float R, G, B, H = 0.0, S, I;
    
    
    // A double for-loop is crated, a for rows (horizontal) of pixels and b for columns (vertical) of pixels. It is done so the programme reads pixels as an darray of horizontal and
    // vertical pixles and later their color values can be changed from RGB values to HSI.
    for(int a = 0; a < source.rows; a++) {
        for(int b = 0; b < source.cols; b++) {
            
            // 3 vectors are created, each for R, G and B, respectively. Vecotrs are a dynamic arrays / mathematical objects that are given a set of elements
            // in a space (in this case an array of pixels). These vectors are using pixels arrays (a-s and b-s) as arguments.
            // at. is used so return a referece from source to the Vec3b at the positions a and b. In other words, we are filling an array Vec3b with pixels from source image file.
            B = source.at<Vec3b>(a, b)[0];
            G = source.at<Vec3b>(a, b)[1];
            R = source.at<Vec3b>(a, b)[2];
            
            // Calculation of the I (intensity) vaule by using R, G and B values from the source image. Mathematical foruma is used and rewritten to suite C++ syntax.
            I = (B + G + R) / 3;
            
            //Including a minimum value is required by the formula of calcualting S (saturation). This is the way of making it.
            //Since min function can only have two arguments, the second argument has to be another min function with two new arguments. This way we can incude
            //all three arguments: R, G, B as arguments of min function.
            int minimum;
            minimum = min(R, min(B, G));
            
            // Calculation of the S (saturation) vaule by using R, G and B values from the source image. Mathematical foruma is used and rewritten to suite C++ syntax.
            S = 1 - 3*(minimum / (B + G + R));
            
            // Calculation of the H (hue) vaule by using R, G and B values from the source image. Mathematical foruma is used and rewritten to suite C++ syntax.
            H = 0.5 * ((R - G) + (R - B)) / sqrt(((R - G) * (R - G)) + ((R - B) * (G - B)));
            H = acos(H);
            
            // 3 if statements are created just in case H, S or I vaues are extreme, then they will be rounded.
            // Not required by the programme in order to run it.
            if(H < 0.001) {
                H = 0;
            }else if(S > 0.999){
                H = 1;
            }
            
            if(S < 0.001) {
                S = 0;
            }else if(S > 0.999){
                S = 1;
            }
            
            if(I < 0.001) {
                I = 0;
            }else if(S > 0.999){
                I = 1;
            }
            
            // Here, we are filling Vec3b array with pixels (which all have changed  values by the calculation done above) from hImage matrix.
            hImage.at<Vec3b>(a, b)[0] = (H * 180) / M_PI;
            
           // Here, we are filling Vec3b array with pixels (which all have changed  values by the calculation done above) from sImage matrix.
            sImage.at<Vec3b>(a, b)[1] = S*100;
            
           // Here, we are filling Vec3b array with pixels (which all have changed  values by the calculation done above) from iImage matrix.
            iImage.at<Vec3b>(a, b)[2] = I;
            
            // Here, we are filling Vec3b arrays with pixels (which all have changed  values by the calculation done above) from HSI matrix. In this case, we have to use all the valyes: H, S and I so we have to use 3 Vec3b arrays.
            HSI.at<Vec3b>(a, b)[0] = (H * 180) / M_PI;
            HSI.at<Vec3b>(a, b)[1] = S*100;
            HSI.at<Vec3b>(a, b)[2] = I;
        }
    }
    
    // Create the window RGB image, name it and display when the program runs.
    namedWindow("Source image in RGB", CV_WINDOW_AUTOSIZE);
    imshow("Source image in RGB", source);
    
    // Create the window H-image, name it and display when the program runs.
    namedWindow("H-image", CV_WINDOW_AUTOSIZE);
    imshow("H-image", hImage);
    
    // Create the window S-image, name it and display when the program runs.
    namedWindow("S-image", CV_WINDOW_AUTOSIZE);
    imshow("S-image", sImage);
    
    // Create the window I-image, name it and display when the program runs.
    namedWindow("I-image", CV_WINDOW_AUTOSIZE);
    imshow("I-image", iImage);
    
    // Create the window HSI image, name it and display when the program runs.
    namedWindow("hsi", CV_WINDOW_AUTOSIZE);
    imshow("hsi", HSI);

    // Program waits for the user to press they key, then the program extis.
    waitKey(0);
    
    // Simple return type for the main function
    return 0;
}
