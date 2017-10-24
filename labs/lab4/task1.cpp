#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <algorithm>

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
                    const int col,
                    const int rowAdjustment,
                    const int colAdjustment) {

    int totalKernelWeight = 0;
    int sum = 0;

    for (int y=0; y<kernel.rows; y++) {
        for (int x=0; x<kernel.cols; x++) {
            totalKernelWeight += kernel.at<uchar>(y, x);
            sum += input.at<uchar>(row + y - rowAdjustment, col + x - colAdjustment) * kernel.at<char>(y, x);
        }
    }

    return (uchar)(sum / totalKernelWeight);
}

void convolve(Mat &input, Mat &kernel, Mat &output){
    output.create(input.size(), CV_8U);

    const int rowAdjustment = (kernel.rows - 1) / 2;
    const int colAdjustment = (kernel.cols - 1) / 2;

    for (int row=rowAdjustment; row<input.rows-rowAdjustment; row++){
        for (int col=colAdjustment; col<input.cols-colAdjustment; col++){
            output.at<uchar>(row, col) = convolvePixel(input, kernel, row, col, rowAdjustment, colAdjustment);
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
