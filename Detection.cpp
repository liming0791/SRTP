#include <QtGui>
#include <QtWidgets>
#include "platform.h"

Detection::Detection(QWidget* parent)
	:face_cascade(),QWidget(parent)
{
	std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
	//face_cascade =cv::CascadeClassifier();
	if(!face_cascade.load(face_cascade_name))
		exit(1);
	//init colorMode
	colorMode = 1;

	//init for hist
	histSize[0] = 256;
	hranges[0] = 0.0;
	hranges[1] = 255.0;
	ranges[0] = hranges;
	channels[0] = 0; // by default, we look at channel 0
}

Detection::~Detection()
{
	//delete face_cascade;
}

void Detection::loadCamera()
{
	capture = cv::VideoCapture(0);
}

void Detection::queryFrame()
{
	capture>>frame;
	flip(frame,frame,1);
	colorMode = 1;
}

cv::Mat& Detection::getPic()
{
	if(colorMode == 1)
	{
		cvtColor(frame,frame,CV_BGR2RGB);
		colorMode = -1;
	}
	return frame;
}

bool Detection::detectFace(double S,int N, int X,int Y)
{	
	if(colorMode == -1)
	{
		cvtColor(frame,frame,CV_RGB2BGR);
		colorMode = 1;
	}
	int width = frame.cols;
	int height = frame.rows;

	std::vector<cv::Rect> faces;
	cv::Mat frame_gray;
	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	/*std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
	cv::CascadeClassifier face_cascade;
	if(!face_cascade.load(face_cascade_name))
		exit(1);*/
	face_cascade.detectMultiScale(frame_gray, faces,S, N, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(X, Y));
	//emit toSetLabel(1,QString::number(S));
	//emit toSetLabel(2,QString::number(N));
	//emit toSetLabel(3,QString::number(X));
	//emit toSetLabel(4,QString::number(Y));
	for (size_t i = 0; i < faces.size(); i++)
	{	
		int x = faces[i].x+faces[i].width*0.5 , y=faces[i].y+faces[i].height*0.5 , width = faces[i].width , height = faces[i].height;

		cv::Point center(x  , y );

		if(x<0.5*X&&x>0.4*X&&y>0.3*Y&&y<0.7*Y){
			sendScreenShot();
		}

		ellipse(frame, center, cv::Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
	}
	return true;
}

cv::MatND Detection::getHistogram() {
		cv::MatND hist;
		// Compute histogram

		if(colorMode == -1)
		{
			cvtColor(frame,frame,CV_RGB2BGR);
			colorMode = 1;
		}
		cv::Mat frame_gray;
		cvtColor(frame, frame_gray, CV_BGR2GRAY);
		cv::calcHist(&frame_gray,
			1, // histogram from 1 image only
			channels, // the channel used
			cv::Mat(), // no mask is used
			hist, // the resulting histogram
			1, // it is a 1D histogram
			histSize, // number of bins
			ranges // pixel value range
			);
		return hist;
	}



cv::Mat Detection::getHistogramImage(){
		// Compute histogram first
		cv::MatND hist = getHistogram();
		// Get min and max bin values
		double maxVal = 0;
		double minVal = 0;
		cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
		// Image on which to display histogram
		static cv::Mat histImg(cv::Size(320,240),
			CV_8UC1, cv::Scalar(255));
		histImg = cv::Scalar(255);
		// set highest point at 90% of nbins
		int hpt = static_cast<int>(0.9*240);
		// Draw a vertical line for each bin
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			// This function draws a line between 2 points
			cv::line(histImg, cv::Point(h, 240),
				cv::Point(h, 240 - intensity),
				cv::Scalar::all(0));
		}
		return histImg;
	}


cv::Mat Detection::getRGBHistogramImage()
{
		// Compute histogram first
		cv::MatND hist_r;
		cv::MatND hist_g;
		cv::MatND hist_b;
		// Compute histogram

		if(colorMode == -1)
		{
			cvtColor(frame,frame,CV_RGB2BGR);
			colorMode = 1;
		}
		int cha_r[] = {0};
		cv::calcHist(&frame,
			1, // histogram from 1 image only
			cha_r, // the channel used
			cv::Mat(), // no mask is used
			hist_r, // the resulting histogram
			1, // it is a 1D histogram
			histSize, // number of bins
			ranges // pixel value range
			);

		int cha_g[] = {1};
		cv::calcHist(&frame,
			1, // histogram from 1 image only
			cha_g, // the channel used
			cv::Mat(), // no mask is used
			hist_g, // the resulting histogram
			1, // it is a 1D histogram
			histSize, // number of bins
			ranges // pixel value range
			);

		int cha_b[] = {2};
		cv::calcHist(&frame,
			1, // histogram from 1 image only
			cha_b, // the channel used
			cv::Mat(), // no mask is used
			hist_b, // the resulting histogram
			1, // it is a 1D histogram
			histSize, // number of bins
			ranges // pixel value range
			);
		// Get min and max bin values
		double maxVal = 0;
		double minVal = 0;
		// Image on which to display histogram
		static cv::Mat RGBHistImg(cv::Size(320,240),
			CV_8UC3, cv::Scalar(255,255,255));
		RGBHistImg = cv::Scalar(255,255,255);
		// set highest point at 90% of nbins
		int hpt = static_cast<int>(0.9*240);
		// Draw a vertical line for each bin in chanel r
		cv::minMaxLoc(hist_r, &minVal, &maxVal, 0, 0);
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist_r.at<float>(h);
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			// This function draws a line between 2 points			
			cv::line(RGBHistImg, cv::Point(h, 240),cv::Point(h, 240 - intensity),cv::Scalar(255,0,0));
		}
		// Draw a vertical line for each bin in chanel g
		cv::minMaxLoc(hist_g, &minVal, &maxVal, 0, 0);
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist_g.at<float>(h);
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			// This function draws a line between 2 points			
			cv::line(RGBHistImg, cv::Point(h, 240),cv::Point(h, 240 - intensity),cv::Scalar(0,255,0));
		}
		// Draw a vertical line for each bin in chanel b
		cv::minMaxLoc(hist_b, &minVal, &maxVal, 0, 0);
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist_b.at<float>(h);
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			// This function draws a line between 2 points			
			cv::line(RGBHistImg, cv::Point(h, 240),cv::Point(h, 240 - intensity),cv::Scalar(0,0,255));
		}

		return RGBHistImg;
	}