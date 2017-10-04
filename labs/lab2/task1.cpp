#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <stdlib.h>
#include <iostream>

using namespace cv;
using namespace std;

void mandrill0(Mat *image,  Mat *output) {
    cvtColor(*image, *output, CV_BGR2HSV);

    for (int y=0; y<image->rows; y++){
        for (int x=0; x<image->cols; x++){
            output->at<Vec3b>(y, x)[0] += -56;
        }
    }
    cvtColor(*output, *output, CV_HSV2BGR);
}

// Shifts the red channel of the image a certain amount.
void mandrill1(Mat *image, Mat *output) {
    int shift = 30; // pixels

    for (int y=0; y<image->rows; y++){
        for (int x=0; x<image->cols; x++){
            int destX = (x + shift) % image->cols;
            int destY = (y + shift) % image->rows;

            // Remove some red (BGR) from the current pixel.
            uchar red   = image->at<Vec3b>(y, x)[2];
            uchar green = image->at<Vec3b>(destY, destX)[1];
            uchar blue  = image->at<Vec3b>(destY, destX)[0];

            output->at<Vec3b>(destY, destX) = Vec3b(blue, green, red);
        }
    }
}

// Hypothisises:
//      mandrill2 is the inverse
void mandrill2(Mat *image, Mat *output) {
    Vec3b v = Vec3b(255, 255, 255);

    // Iterate through each pixel
    for (int y=0; y<image->rows; y++){
        for (int x=0; x<image->cols; x++){
            // Do the thresholding
            Vec3b pixel = image->at<Vec3b>(y,x);
            output->at<Vec3b>(y, x) = v - pixel;
        }
    }
}

void mandrill3(Mat *image, Mat *output) {
    //output = Mat(image->rows, iamge->cols, )
    // cvtColor(*image, *output, COLOR_BGR2HSV);

    // for (int y=0; y<image->rows; y++){
    //     for (int x=0; x<image->cols; x++){
    //         output->at<Vec3b>(y, x) = image->at<Vec3b>(y, x);
    //     }
    // }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Incorrect number of arguments. Expected the image index.\n";
        return 0;
    }

    int imageIndex = atoi(argv[1]);

    // Read in the image
    //stringstream fileName = "images/mandrill" << imageIndex << ".jpg";

    Mat image, newImage;

    switch (imageIndex) {
        case 0:
            image = imread("images/mandrill0.jpg", CV_LOAD_IMAGE_COLOR);
            newImage = Mat(image.rows, image.cols, CV_8UC3);
            mandrill0(&image, &newImage);
            break;
        case 1:
            image = imread("images/mandrill1.jpg", CV_LOAD_IMAGE_COLOR);
            newImage = Mat(image.rows, image.cols, CV_8UC3);
            mandrill1(&image, &newImage);
            break;
        case 2:
            image = imread("images/mandrill2.jpg", CV_LOAD_IMAGE_COLOR);
            newImage = Mat(image.rows, image.cols, CV_8UC3);
            mandrill2(&image, &newImage);
            break;
        case 3:
            image = imread("images/mandrill3.jpg", CV_LOAD_IMAGE_COLOR);
            // newImage = Mat(image.rows, image.cols, CV_8UC3);
            mandrill3(&image, &newImage);
            break;
        default:
            cout << "Incorrect image index. Must be in the range 0-3\n";
            return 0;
    }

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", newImage);             // Show our image inside it.
    waitKey(0);

    return 0;
}
