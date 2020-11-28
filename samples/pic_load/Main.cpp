#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Main.h"

int main (int argc, char *argv[]) 
{
  cv::Mat image=cv::imread("AR.png");
  if(image.empty())
  {
  	std::cerr << "Could not load image";
  	return 1;
  }
  cv::namedWindow("Image");
  cv::imshow("Image", image);
  cv::waitKey();
  return 0;
}
