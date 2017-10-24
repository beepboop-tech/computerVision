#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <algorithm>

#define KERNEL_SIZE 3
#define ADJUSTMENT (KERNEL_SIZE-1)/2
#define KERNEL_TYPE char
#define KERNEL_CV_TYPE CV_8S

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
            totalKernelWeight += (int)kernel.at<KERNEL_TYPE>(y, x);
            sum += ((int)input.at<uchar>(row + y - ADJUSTMENT, col + x - ADJUSTMENT)) * ((int)kernel.at<KERNEL_TYPE>(y, x));
        }
    }

    int correctedWeight = totalKernelWeight == 0 ? 1 : totalKernelWeight;

    return (uchar)(sum / correctedWeight);
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
    Mat image = imread("images/coins1.png", CV_LOAD_IMAGE_COLOR);
    Mat greyscale;
    cvtColor(image, greyscale, CV_BGR2GRAY);

    Mat output;

    KERNEL_TYPE k[KERNEL_SIZE][KERNEL_SIZE] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    //KERNEL_TYPE k[KERNEL_SIZE][KERNEL_SIZE] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    Mat kernel(KERNEL_SIZE, KERNEL_SIZE, KERNEL_CV_TYPE, k);



    convolve(greyscale, kernel, output);

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", output);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
