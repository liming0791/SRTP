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

