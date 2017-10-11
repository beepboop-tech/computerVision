// header inclusion
#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup
#include <algorithm>


using namespace cv;
using namespace std;

void gaussianBlur(Mat &input, int size,Mat &blurredOutput){
    // intialise the output using the input
	blurredOutput.create(input.size(), input.type());

	// create the Gaussian kernel in 1D
	Mat kX = getGaussianKernel(size, -1);
	Mat kY = getGaussianKernel(size, -1);

	// make it 2D multiply one by the transpose of the other
	Mat kernel = kX * kY.t();

	//CREATING A DIFFERENT IMAGE kernel WILL BE NEEDED
	//TO PERFORM OPERATIONS OTHER THAN GUASSIAN BLUR!!!

	// we need to create a padded version of the input
	// or there will be border effects
	int kernelRadiusX = ( kernel.size[0] - 1 ) / 2;
	int kernelRadiusY = ( kernel.size[1] - 1 ) / 2;

	Mat paddedInput;
	copyMakeBorder( input, paddedInput,
		kernelRadiusX, kernelRadiusX, kernelRadiusY, kernelRadiusY,
		BORDER_REPLICATE );

	// now we can do the convoltion
	for ( int i = 0; i < input.rows; i++ )
	{
		for( int j = 0; j < input.cols; j++ )
		{
			double sum = 0.0;
			for( int m = -kernelRadiusX; m <= kernelRadiusX; m++ )
			{
				for( int n = -kernelRadiusY; n <= kernelRadiusY; n++ )
				{
					// find the correct indices we are using
					int imagex = i + m + kernelRadiusX;
					int imagey = j + n + kernelRadiusY;
					int kernelx = m + kernelRadiusX;
					int kernely = n + kernelRadiusY;

					// get the values from the padded image and the kernel
					int imageval = ( int ) paddedInput.at<uchar>( imagex, imagey );
					double kernalval = kernel.at<double>( kernelx, kernely );

					// do the multiplication
					sum += imageval * kernalval;
				}
			}
			// set the output value as the sum of the convolution
			blurredOutput.at<uchar>(i, j) = (uchar) sum;
		}
	}
}

uchar convolve(Mat *image, int x, int y, int kernelDimension){
    int pixels[kernelDimension*kernelDimension];
    int imageReduction = (kernelDimension-1)/2;
    int insertPixelIndex = 0;

    for (int i=-imageReduction; i<imageReduction; i++){
        for (int j=-imageReduction; j<imageReduction; j++){
            pixels[insertPixelIndex] = image->at<uchar>(y+i, x+j);
            insertPixelIndex++;
        }
    }
    sort(pixels, pixels+(insertPixelIndex-1));
    return pixels[(insertPixelIndex-1)/2];
}

int main(int argc, char *argv[]) {
    int kernelDimension = 5;
    int imageReduction  = (kernelDimension-1);
    // Read in the image
    Mat image  = imread("images/car2.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat output = Mat(image.rows-imageReduction, image.cols-imageReduction, CV_8U);

    // Iterate through each pixel
    // NOTE: The perimeter rows/cols are ignored
    for (int y=1; y<image.rows-imageReduction; y++){
        for (int x=1; x<image.cols-imageReduction; x++){
            output.at<uchar>(y,x) = convolve(&image, x, y, kernelDimension);
        }
    }

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", output);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
