#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
//#include<conio.h>         
using namespace cv;
using namespace std;
int main() {
CvCapture* capture = cvCreateCameraCapture(0);   // declare a VideoCapture object to associate webcam, 0 means use 1st (default) webcam
cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
 /*if (capWebcam.isOpened() == false)  //  To check if object was associated to webcam successfully
 {
  std::cout << "error: Webcam connect unsuccessful\n"; // if not then print error message
  return(0);            // and exit program
 }*/

 cv::Mat imgOriginal;        // input image
 cv::Mat imgGrayscale;       // grayscale image
 cv::Mat imgBlurred;         // blured image
 cv::Mat imgCanny;           // Canny edge image
 cv::Mat bin;

 char charCheckForEscKey = 0;
 int lowTh = 45;
 int highTh = 90;

 while (charCheckForEscKey != 27) {            // until the Esc key is pressed or webcam connection is lost
  /*bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);   // get next frame

  if (!blnFrameReadSuccessfully || imgOriginal.empty()) {    // if frame read unsuccessfully
   std::cout << "error: frame can't read \n";      // print error message
   break;               
  }
*/
imgOriginal = cvQueryFrame(capture);
  cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);                   // convert to grayscale

  cv::GaussianBlur(imgGrayscale,imgBlurred,cv::Size(5, 5),1.8);           // Blur Effect             

  cv::Canny(imgBlurred,imgCanny,lowTh,highTh);       // Canny Edge Image


	// преобразуем в двоичное
	inRange(imgCanny, Scalar(40), Scalar(150), bin); // atoi(argv[2])

	//CvMemStorage* storage = cvCreateMemStorage(0);
	//CvSeq* contours=0;
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
	// находим контуры
	//int contoursCont = cv::findContours(imgCanny, storage, &contours , sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));


//cv::findContours(imgCanny, storage, &contours , sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));
  //cv::findContours(imgCanny, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

  //declare windows
  cv::namedWindow("imgOriginal", CV_WINDOW_NORMAL);      
  cv::namedWindow("imgCanny", CV_WINDOW_NORMAL);    
  //declare trackbar
  cv::createTrackbar("LowTh", "imgCanny", &lowTh, 100);
  cv::createTrackbar("HighTh", "imgCanny", &highTh, 100);
  // show windows
  cv::imshow("imgOriginal", imgOriginal);                 
  cv::imshow("imgCanny", imgCanny);                       

  charCheckForEscKey = cv::waitKey(1);        // delay and get key press
 }

 return(0);
}
