#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <stdlib.h>
#include <iostream>

using namespace cv;
using namespace std;

void mandrill0(Mat *image) {

}

void mandrill1(Mat *image) {

}

// Hypothisises:
//      mandrill2 is the inverse
void mandrill2(Mat *image) {
    Vec3b v = Vec3b(255, 255, 255);

    // Iterate through each pixel
    for (int y=0; y<image->rows; y++){
        for (int x=0; x<image->rows; x++){
            // Do the thresholding
            Vec3b pixel = image->at<Vec3b>(y,x);
            image->at<Vec3b>(y, x) = v - pixel;
        }
    }
}

void mandrill3(Mat *image) {

}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Incorrect number of arguments. Expected the image index.\n";
        return 0;
    }

    int imageIndex = atoi(argv[1]);

    // Read in the image
    //stringstream fileName = "images/mandrill" << imageIndex << ".jpg";

    Mat image;

    switch (imageIndex) {
        case 0:
            image = imread("images/mandrill0.jpg", CV_LOAD_IMAGE_COLOR);
            mandrill0(&image);
            break;
        case 1:
            image = imread("images/mandrill1.jpg", CV_LOAD_IMAGE_COLOR);
            mandrill1(&image);
            break;
        case 2:
            image = imread("images/mandrill2.jpg", CV_LOAD_IMAGE_COLOR);
            mandrill2(&image);
            break;
        case 3:
            image = imread("images/mandrill3.jpg", CV_LOAD_IMAGE_COLOR);
            mandrill3(&image);
            break;
        default:
            cout << "Incorrect image index. Must be in the range 0-3\n";
            return 0;
    }

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", image);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
