#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;


int main() {
    // Read in the image
    Mat image;
    image = imread("mandrill.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // Iterate through each pixel
    // TODO

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", image);                   // Show our image inside it.
    waitKey(0);
    
    return 0;
}
