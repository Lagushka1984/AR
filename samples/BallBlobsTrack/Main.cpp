#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
 
using namespace cv;
using std::cout;
using std::endl;
 
int main(int argc, char **argv){

	int WHITE[6] {0, 255, 0, 30, 145, 255};
	int GREEN[6] {0, 255, 50, 255, 143, 255};

    char mainWindow[] = "Main";
    char trackbarWindow[] = "Trackbar";
    char thresholdWindow[] = "No GREEN?WHITE";
    char thresholdWindow1[] = "WHITE";
    char thresholdWindow2[] = "CUSTOM";
    int min = 0, max = 1000;
    int hmin = 0, smin = 0, vmin = 0,
        hmax = 255, smax = 255, vmax = 255;
    Mat frame, HSV, threshold, blurred, threshold1, threshold2;
    VideoCapture capture;
    
    CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours=0;

    //Создаем окна
    namedWindow(mainWindow, 0);
    namedWindow(trackbarWindow, 0);
    namedWindow(thresholdWindow, 0);
    namedWindow(thresholdWindow1, 0);
    namedWindow(thresholdWindow2, 0);
    
    //Создаем трэкбар
    createTrackbar("H min:", trackbarWindow, &hmin, hmax);
    createTrackbar("H max:", trackbarWindow, &hmax, hmax);
    createTrackbar("S min:", trackbarWindow, &smin, smax);
    createTrackbar("S max:", trackbarWindow, &smax, smax);
    createTrackbar("V min:", trackbarWindow, &vmin, vmax);
    createTrackbar("V max:", trackbarWindow, &vmax, vmax);
    createTrackbar("Size min:", trackbarWindow, &min, max);
    createTrackbar("Size max:", trackbarWindow, &max, max);
    
    //Открываем камеру
    capture.open(0);
    if(!capture.isOpened())
    {
        cout << "Камера не может быть открыта." << endl;
        exit(1);
    }
    
    //Запускаем цикл чтения с камеры
    for(;;){
        capture >> frame;
        cvtColor(frame, HSV, COLOR_BGR2HSV);
        medianBlur(HSV, blurred, 21);

        inRange(blurred, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), threshold2);
        inRange(blurred, Scalar(WHITE[0], WHITE[2], WHITE[4]), Scalar(WHITE[1], WHITE[3], WHITE[5]), threshold1);
        inRange(blurred, Scalar(GREEN[0], GREEN[2], GREEN[4]), Scalar(GREEN[1], GREEN[3], GREEN[5]), threshold);
        //cvCvtColor(threshold, threshold, CV_RGB2GRAY);
		//cvCanny(threshold, threshold, 10, 100, 3);
        /*
        for(int y = 0; y < threshold.rows; y++){
            for(int x = 0; x < threshold.cols; x++){
                int value = threshold.at<uchar>(y, x);
                if(value == 255){
                    Rect rect;
                    int count = floodFill(threshold, Point(x, y), Scalar(200), &rect);
                    if(rect.width >= min && rect.width <= max && rect.height >= min && rect.height <= max){
                        rectangle(frame, rect, Scalar(255, 0, 255, 4));
                    }
                }
            }
        }
        */
        imshow(mainWindow, frame);
        imshow(thresholdWindow, threshold);nj6ffff
        imshow(thresholdWindow1, threshold1);
        imshow(thresholdWindow2, threshold2);
        if(waitKey(33) == 27) break;
    }
    return 0;
}