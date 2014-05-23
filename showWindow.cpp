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
}

void showWindow::showImage(cv::Mat& img)
{	 

	qImg = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
	label = new QLabel(this);
	label->setScaledContents(true);
	//label->move(200, 50);  
	label->setPixmap(QPixmap::fromImage(qImg));  
	label->resize(320,240);      
	label->show();
}

void showWindow::showGrayHistgram(cv::Mat& img)
{
	qImg = QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_Indexed8);
	label = new QLabel(this);
	label->setScaledContents(true);
	//label->move(200, 50);  
	label->setPixmap(QPixmap::fromImage(qImg));  
	label->resize(320,240);      
	label->show();
}