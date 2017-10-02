#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <stdlib.h>

using namespace cv;


// Hypothisises:
//      mandrill2 is the inverse

int main(int argc, char *argv[]) {
    // Read in the image
    Mat image;
    image = imread("images/mandrill2.jpg", CV_LOAD_IMAGE_COLOR);

    Vec3b v = Vec3b(255, 255, 255);




    // Iterate through each pixel
    for (int y=0; y<image.rows; y++){
        for (int x=0; x<image.rows; x++){
            // Do the thresholding
            Vec3b pixel = image.at<Vec3b>(y,x);
            image.at<Vec3b>(y, x) = v - pixel;
        }
    }

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", image);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
