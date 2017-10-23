// header inclusion
#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <algorithm>


using namespace cv;

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


//
// uchar convolvePixel(Mat *image, int x, int y, int kernelDimension){
//     int pixels[kernelDimension*kernelDimension];
//     int imageReduction = (kernelDimension-1)/2;
//     int insertPixelIndex = 0;
//
//     for (int i=-imageReduction; i<imageReduction; i++){
//         for (int j=-imageReduction; j<imageReduction; j++){
//             pixels[insertPixelIndex] = image->at<uchar>(y+i, x+j);
//             insertPixelIndex++;
//         }
//     }
//     sort(pixels, pixels+(insertPixelIndex-1));
//     return pixels[(insertPixelIndex-1)/2];
// }

uchar convolvePixel(Mat &input,
                    Mat &kernel,
                    const int row,
                    const int col) {

    int totalKernelWeight = 0;
    int sum = 0;

    for (int y=0; y<kernel.rows; y++) {
        for (int x=0; x<kernel.cols; x++) {
            totalKernelWeight += kernel.at<uchar>(y, x);
            sum += input.at<uchar>(row + y, col + x) * kernel.at<uchar>(row - y, col - x);
        }
    }

    return (uchar)(sum / totalKernelWeight);
}

Mat convolve(Mat &input, Mat &kernel, Mat &output){
    output.create(input.size(), input.type());

    const int rowAdjustment = (kernel.rows - 1) / 2;
    const int colReduction = (kernel.cols - 1) / 2;

    for (int row=rowAdjustment; row<input.rows-rowAdjustment; row++){
        for (int col=colReduction; col<input.cols-colReduction; col++){
            output.at<uchar>(row, col) = convolvePixel(input, kernel, row, col);
        }
    }
}


int main(int argc, char *argv[]) {
    // Read in the image
    Mat image = imread("images/coin1.png", CV_LOAD_IMAGE_COLOR);
    Mat output;

    // uchar k = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    // Mat kernel =

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", output);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
