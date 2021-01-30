#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>      

using namespace cv;
using namespace std;

Point GetBall(Mat img)
{
	Point Balls[100];
	int RD[100];
	int count = 0;

	cvtColor(img, img, CV_BGR2GRAY);                
	GaussianBlur(img, img, Size(5, 5),1.8);  
	Canny(img, img, 45, 90);  

	vector<Vec3f> circles;
	HoughCircles(img, circles, CV_HOUGH_GRADIENT, 1, img.rows/16, 100, 30, 1, 30);
	for (size_t i = 0; i < circles.size(); i++)
		{
			Vec3i c = circles[i];
			Point center = Point(c[0], c[1]);
			Balls[i] = center;
			RD[i] = c[2];
			count++;
		}

	int max = 0;
	Point Ball;
	for (int i = 0; i < count; i++)
	{
		if (RD[i] > max)
		{
			Ball = Balls[i];
			max = RD[i];
		}
	}
	return Ball;
}

int main() {
	CvCapture* capture = cvCreateCameraCapture(1);  
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
	
	Mat imgOriginal;     
 	char charCheckForEscKey = 0;
 	Point Ball;
 	Point Last = Ball;
	namedWindow("imgCanny", CV_WINDOW_NORMAL);

	 while (charCheckForEscKey != 27) 
	 {          
		imgOriginal = cvQueryFrame(capture);
		Ball = GetBall(imgOriginal);     
		if (Ball != Point(0, 0)) Last = Ball;
		else Ball = Last;       
		cout<<Ball<<'\n';    
		circle(imgOriginal, Ball, 4, Scalar(255, 0, 0), 3, CV_AA);  
		imshow("imgCanny", imgOriginal);  
		if(waitKey(33) == 27) break;
	 }
	return(0);
}
