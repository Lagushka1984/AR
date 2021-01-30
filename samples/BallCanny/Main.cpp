#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>      

using namespace cv;
using namespace std;

#define WINDOW 1;

int main() {
	CvCapture* capture = cvCreateCameraCapture(0);  
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
	
	cv::Mat imgOriginal;        // input image
	cv::Mat imgGrayscale;       // grayscale image
	cv::Mat imgBlurred;         // blured image
	cv::Mat imgCanny;           // Canny edge image
	cv::Mat bin;

 	char charCheckForEscKey = 0;
 	int lowTh = 45;
 	int highTh = 90;

	 while (charCheckForEscKey != 27) 
	 {          
		 imgOriginal = cvQueryFrame(capture);
		 cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);                
		 cv::GaussianBlur(imgGrayscale,imgBlurred,cv::Size(5, 5),1.8);  
		 cv::Canny(imgBlurred,imgCanny,lowTh,highTh);   

		 vector<Vec3f> circles;
		 HoughCircles(imgCanny, circles,CV_HOUGH_GRADIENT, 1, bin.rows/16, 100, 30, 1, 30);
		 for (size_t i = 0; i < circles.size(); i++)
		 {
			 Vec3i c = circles[i];
			 Point center = Point(c[0], c[1]);
			 circle(imgCanny, center, 1, Scalar(0, 100, 100), 3, CV_AA);
			 int radius = c[2];
			 circle(imgCanny, center, radius, Scalar(255, 0, 255), 3, CV_AA);
		 }
		 
		 if (WINDOW == 1)
		 {    
			 cv::namedWindow("imgCanny", CV_WINDOW_NORMAL);                    
			 cv::imshow("imgCanny", imgCanny);   
		 }
	 }
	return(0);
}
