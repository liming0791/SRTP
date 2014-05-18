#include <QtGui>
#include <QtWidgets>
#include "platform.h"

showWindow::showWindow( QWidget* parent)
	:QWidget(parent)
{
	this->setMinimumSize(320,240);
	this->resize(320,240);
	
}

showWindow::~showWindow()
{
	delete label;
}

void showWindow::showImage(cv::Mat img, int& colorMode)
{	
	if(colorMode==1)
	{
		cv::cvtColor(img,img,CV_BGR2RGB);
		colorMode = -1;
	}

	qImg = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
	label = new QLabel(this);
	label->setScaledContents(true);
	//label->move(200, 50);  
	label->setPixmap(QPixmap::fromImage(qImg));  
	label->resize(320,240);      
	label->show();

	//cv::cvtColor(img,img,CV_RGB2BGR);
}

//void showWindow::showAgainImage(cv::Mat& img)
//{	
//	
//	static QImage qImg = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
//
//	static QLabel label(this);
//	label.setScaledContents(true);
//	//label->move(200, 50);  
//	label.setPixmap(QPixmap::fromImage(qImg));  
//	label.resize(320,240);      
//	label.show();
//}

//void showWindow::showVedio(cv::VideoCapture cap)
//{	
//	capture = cap;
//	double rate= capture.get(CV_CAP_PROP_FPS);
//	
//	timer->start(1000/rate);
//		
//
//}

//void showWindow::showFrame()
//{	
//	//frame = new cv::Mat(); 
//	capture.read(frame);
//	
//	if(ifShot==1)
//	{	 
//		
//		QDateTime time = QDateTime::currentDateTime();  
//		QString filename = time.toString("yyyy-MM-dd hh-mm-ss");
//		cv::imwrite("screenshot"+filename.toStdString()+".png",frame);
//
//		showImage(frame);
//		emit sendScreenShot(frame);
//		ifShot = 0;
//	}
//	else
//		showImage(frame);
//	
//}

//void showWindow::screenShot()
//{
//	ifShot = 1;
//}
//
//void showWindow::stopVideo()
//{
//	timer->stop();
//	timer2->stop();
//	if(capture.isOpened())
//		capture.release();
//}
//
//void showWindow::showScreenShot(cv::Mat& screenShot){
//	this->showAgainImage(screenShot);
//}
//
//void showWindow::loadCamera()
//{
//	capture = cv::VideoCapture(0);
//	//double rate= capture.get(CV_CAP_PROP_FPS);
//	
//	timer2->start(1000/60);
//
//		/*while(1)
//		{*/
//			/*capture>>frame;
//			showImage(frame);*/
//		//}
//	
//}
//
//void showWindow::detectAndDisplay()
//{
//	capture>>frame;
//	//cvFlip(frame.data,frame.data,1);
//
//	int X = frame.cols;
//	int Y = frame.rows;
//	
//	if(ifShot==1)
//	{	
//		QDateTime time = QDateTime::currentDateTime();  
//  
//		QString filename = time.toString("yyyy-MM-dd hh-mm-ss");
//		
//		cv::imwrite("screenshot"+filename.toStdString()+".png",frame);
//
//		cv::cvtColor(frame,frame,CV_BGR2RGB);
//		emit sendScreenShot(frame);
//		cv::cvtColor(frame,frame,CV_RGB2BGR);
//		ifShot =0;
//	}
//	//capture>>img;
//	std::vector<cv::Rect> faces;
//	cv::Mat frame_gray;
//	cvtColor(frame, frame_gray, CV_BGR2GRAY);
//	equalizeHist(frame_gray, frame_gray);
//
//	//-- Detect faces
//	cv::CascadeClassifier face_cascade;
//	if (!face_cascade.load(face_cascade_name)){ printf("--(!)Error loading\n");  };
//
//	face_cascade.detectMultiScale(frame_gray, faces,scaleFactor, minNeighbors, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(minX, minY));
//	emit toSetLabel(1,QString::number(scaleFactor));
//	emit toSetLabel(2,QString::number(minNeighbors));
//	emit toSetLabel(3,QString::number(minX));
//	emit toSetLabel(4,QString::number(minY));
//	for (size_t i = 0; i < faces.size(); i++)
//	{	
//		int x = faces[i].x+faces[i].width*0.5 , y=faces[i].y+faces[i].height*0.5 , width = faces[i].width , height = faces[i].height;
//
//		cv::Point center(x  , y );
//
//		if(x<0.5*X&&x>0.4*X&&y>0.3*Y&&y<0.7*Y){
//			cv::cvtColor(frame,frame,CV_BGR2RGB);
//			emit sendScreenShot(frame);
//			cv::cvtColor(frame,frame,CV_RGB2BGR);
//		}
//
//		ellipse(frame, center, cv::Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
//	}
//
//	showImage(frame);
//
//	
//	//-- Show what you got
//
//}
//
//void showWindow::setScaleFactor(double S)
//{
//	scaleFactor = S;
//
//	
//}
//
//void showWindow::setMinNeighbors(int N)
//{
//	minNeighbors = N;
//	
//}
//
//void showWindow::setMinX(int x)
//{
//	minX = x; 
//	
//}
//
//void showWindow::setMinY(int y)
//{
//	minY = y;
//	
//}

