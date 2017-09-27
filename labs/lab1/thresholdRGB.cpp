#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <stdlib.h>

using namespace cv;

uchar threshold(uchar channelVal, int thresholdVal){
    return channelVal < thresholdVal ? 0 : 255;
}

int main(int argc, char *argv[]) {
    int thresholdVal = (argc<2) ? 128: atoi(argv[1]);

    // Read in the image
    Mat image;
    image = imread("mandrillRGB.jpg", CV_LOAD_IMAGE_COLOR);

    // Iterate through each pixel
    for (int y=0; y<image.rows; y++){
        for (int x=0; x<image.rows; x++){
            // Do the thresholding
            Vec3b pixel = image.at<Vec3b>(y,x);
            for (int c=0; c<3; c++) {
                image.at<Vec3b>(y, x)[c] = threshold(pixel[c], thresholdVal);
            }
        }
    }

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", image);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
