#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <stdlib.h>

using namespace cv;

int main(int argc, char *argv[]) {
    int threshold = (argc<2) ? 128: atoi(argv[1]);

    // Read in the image
    Mat image;
    image = imread("mandrill.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // Iterate through each pixel
    for (int y=0; y<image.rows; y++){
        for (int x=0; x<image.rows; x++){
            // Do the thresholding
            uchar pixel = image.at<uchar>(y,x);
            image.at<uchar>(y,x) = (pixel < threshold)? 0: 255;
        }
    }

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", image);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
