#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main(int argc, char* argv[])
{
	// получаем любую подключённую камеру
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY); //cvCaptureFromCAM( 0 );
	assert( capture );

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);//1280); 
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);//960); 

	// узнаем ширину и высоту кадра
	double width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	double height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	printf("[i] %.0f x %.0f\n", width, height );

	IplImage* frame=0;

	cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);

	printf("[i] press Enter for capture image and Esc for quit!\n\n");

	int counter=0;
	char filename[512];
	int x_sum = 0;
	int y_sum= 0;
	int x_ct = 0;
	int y_ct = 0;
	int x = 0;
	int y = 0;
	while(true){
		x_ct = 0;
		y_ct = 0;
		x_sum = 0;
		y_sum = 0;
		// получаем кадр
		frame = cvQueryFrame( capture );
		Mat img = frame;
		for (int i = 0; i < img.rows; i = i + 4)
			for (int j = 0; j < img.cols; j = j + 4)
			if (img.at<Vec3b>(i, j)[0] <  img.at<Vec3b>(i, j)[2] - 60 && img.at<Vec3b>(i, j)[1] < img.at<Vec3b>(i, j)[2] - 60 && img.at<Vec3b>(i, j)[2] >  100)
			{
				img.at<Vec3b>(i, j)[0] = 0;
				img.at<Vec3b>(i, j)[1] = 0;
				img.at<Vec3b>(i, j)[2] = 255;
 				x_sum = x_sum + i;
				y_sum = y_sum + j;
				x_ct++;
				y_ct++;
			}
		if (x_ct != 0 and y_ct != 0) 
		{
			y = x_sum /  x_ct;
			x = y_sum / y_ct;
			std::cout<<"x: "<<x<<"         y: "<<y<<'\n';	
			circle(img, Point(x, y), 10, Scalar(0, 255, 0), 10);
		}
		// показываем
		cvShowImage("capture", frame);
	
		char c = cvWaitKey(33);
		if (c == 27) { // нажата ESC
			break;
		}
		else if(c == 13) { // Enter
			// сохраняем кадр в файл
			sprintf(filename, "Image%d.jpg", counter);
			printf("[i] capture... %s\n", filename);
			cvSaveImage(filename, frame);
			counter++;
		}
	}
	// освобождаем ресурсы
	cvReleaseCapture( &capture );
	cvDestroyWindow("capture");
	return 0;
}