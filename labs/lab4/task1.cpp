#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <algorithm>
#include <math.h>

#define KERNEL_SIZE 3
#define ADJUSTMENT (KERNEL_SIZE-1)/2
#define KERNEL_TYPE char
#define KERNEL_CV_TYPE CV_8S

using namespace cv;
using namespace std;

KERNEL_TYPE convolvePixel(Mat &input,
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

    if (sum / correctedWeight < -128) {
        return -128;
    }

    if (sum / correctedWeight > 128) {
        return 127;
    }


    return (KERNEL_TYPE)(sum / correctedWeight);
}

void convolve(Mat &input, KERNEL_TYPE k[KERNEL_SIZE][KERNEL_SIZE], Mat &output){
    Mat kernel(KERNEL_SIZE, KERNEL_SIZE, KERNEL_CV_TYPE, k);
    output.create(input.size(), KERNEL_CV_TYPE);

    for (int row=ADJUSTMENT; row<input.rows-ADJUSTMENT; row++){
        for (int col=ADJUSTMENT; col<input.cols-ADJUSTMENT; col++){
            output.at<KERNEL_TYPE>(row, col) = convolvePixel(input, kernel, row, col);
        }
    }
}

class SobelData {
public:
    Mat greyscaleImage;
    Mat image;
    Mat dX;
    Mat dY;
    Mat magGrad;
    Mat dirGrad;
    SobelData(Mat);
};

SobelData::SobelData(Mat inputImage):image(inputImage){
    cvtColor(this->image, this->greyscaleImage, CV_BGR2GRAY);

    KERNEL_TYPE ySobel[KERNEL_SIZE][KERNEL_SIZE] = {{-1, -2, -1}, { 0, 0, 0}, { 1,  2, 1}};
    KERNEL_TYPE xSobel[KERNEL_SIZE][KERNEL_SIZE] = {{-1,  0,  1}, {-2, 0, 2}, {-1, -0, 1}};

    convolve(this->greyscaleImage, ySobel, this->dY);
    convolve(this->greyscaleImage, xSobel, this->dX);

    // Gradient Magnitude and Direction
    magGrad.create(this->greyscaleImage.size(), KERNEL_CV_TYPE);
    dirGrad.create(this->greyscaleImage.size(), KERNEL_CV_TYPE);
    for (int row=0; row<this->greyscaleImage.rows; row++){
        for (int col=0; col<this->greyscaleImage.cols; col++){
            float x = (float) this->dX.at<KERNEL_TYPE>(row, col);
            float y = (float) this->dY.at<KERNEL_TYPE>(row, col);

            this->magGrad.at<KERNEL_TYPE>(row, col) = (KERNEL_TYPE) hypot(x,y);
            this->dirGrad.at<KERNEL_TYPE>(row, col) = ((atan2(y,x)*180)/M_PI) * (256.0/360);
        }
    }
}








int main(int argc, char *argv[]) {
    // Read in the image
    Mat image = imread("images/coins1.png", CV_LOAD_IMAGE_COLOR);
    SobelData data(image);



    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", data.dirGrad);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
