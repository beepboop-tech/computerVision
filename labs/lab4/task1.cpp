#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <algorithm>

#define KERNEL_SIZE 3
#define ADJUSTMENT (KERNEL_SIZE-1)/2

using namespace cv;
using namespace std;

class SobelData {
private:
    Mat image;
    Mat dX;
    Mat dY;
    Mat magGrad;
    Mat dirGrad;

public:
    SobelData(Mat);
};

SobelData::SobelData(Mat inputImage):image(inputImage){

}


uchar convolvePixel(Mat &input,
                    Mat &kernel,
                    const int row,
                    const int col) {

    int totalKernelWeight = 0;
    int sum = 0;

    for (int y=0; y<kernel.rows; y++) {
        for (int x=0; x<kernel.cols; x++) {
            totalKernelWeight += kernel.at<uchar>(y, x);
            sum += input.at<uchar>(row + y - ADJUSTMENT, col + x - ADJUSTMENT) * kernel.at<char>(y, x);
        }
    }

    return (uchar)(sum / totalKernelWeight);
}

void convolve(Mat &input, Mat &kernel, Mat &output){
    output.create(input.size(), CV_8U);

    for (int row=ADJUSTMENT; row<input.rows-ADJUSTMENT; row++){
        for (int col=ADJUSTMENT; col<input.cols-ADJUSTMENT; col++){
            output.at<uchar>(row, col) = convolvePixel(input, kernel, row, col);
        }
    }
}



int main(int argc, char *argv[]) {
    // Read in the image
    Mat image = imread("images/coins3.png", CV_LOAD_IMAGE_COLOR);
    Mat greyscale;
    cvtColor(image, greyscale, CV_BGR2GRAY);

    Mat output;

    const int kernelSize = 3;
    char k[kernelSize][kernelSize] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    Mat kernel(kernelSize, kernelSize, CV_8S, k);

    convolve(greyscale, kernel, output);

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", output);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
