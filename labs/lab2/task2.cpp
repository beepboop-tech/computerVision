#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <stdlib.h>

using namespace cv;

uchar threshold(uchar channelVal, int thresholdVal){
    return channelVal < thresholdVal ? 0 : 255;
}

uchar convolve(Mat *image, int x, int y){
    int total = 0;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            total += (int) image->at(y-i, x-j);
        }
    }
    return (uchar) (total/9);
}

int main(int argc, char *argv[]) {
    int thresholdVal = (argc<2) ? 128: atoi(argv[1]);

    // Read in the image
    Mat image;
    image = imread("mandrillRGB.jpg", CV_LOAD_GRAYSCALE);

    Mat output;
    output = Mat(image.rows-2, image.cols-2, CV_8UC1);

    // Iterate through each pixel
    // NOTE: The perimeter rows/cols are ignored
    for (int y=1; y<image.rows-1; y++){
        for (int x=1; x<image.cols-1; x++){

            output.at<Vec3b>(y,x) = convolve(&image, x, y);

        }
    }

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", output);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
