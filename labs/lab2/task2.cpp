#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <stdlib.h>
#include <iostream>

using namespace cv;
using namespace std;

uchar convolve(Mat *image, int x, int y){
    int total = 0;
    for (int i=-1; i<1; i++){
        for (int j=-1; j<1; j++){
            total += (int) image->at<uchar>(y+i, x+j);
        }
    }

    return (uchar) (total/9);
}

int main(int argc, char *argv[]) {
    // Read in the image
    Mat image  = imread("images/mandrill.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat output = Mat(image.rows-2, image.cols-2, CV_8U);

    // Iterate through each pixel
    // NOTE: The perimeter rows/cols are ignored
    for (int y=1; y<image.rows-1; y++){
        for (int x=1; x<image.cols-1; x++){
            output.at<uchar>(y,x) = convolve(&image, x, y);
        }
    }

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", output);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
