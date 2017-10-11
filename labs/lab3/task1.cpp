// header inclusion
#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;

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


int main (void){
    Mat image = imread("./images/car1.png", CV_LOAD_IMAGE_COLOR);



    Mat grayImage;
    cvtColor( image, grayImage, CV_BGR2GRAY );

    Mat currImage = grayImage;

    for (int i=0; i<7; i++) {
        Mat blurredImage;
        gaussianBlur(currImage, 5, blurredImage);

        currImage = currImage * 2 - blurredImage;
    }


    // Mat carBlurred;
    // gaussianBlur(grayImage,50,carBlurred);
    //
    // Mat sharpened;
    // sharpened.create(grayImage.size(), grayImage.type());
    //
    //
    // for (int y=0; y<grayImage.rows; y++){
    //     for (int x=0; x<grayImage.cols; x++){
    //         sharpened.at<uchar>(y,x) = grayImage.at<uchar>(y,x)*2 - carBlurred.at<uchar>(y,x);
    //     }
    // }

    // Write the output
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", currImage);                   // Show our image inside it.
    waitKey(0);

    return 0;
}
