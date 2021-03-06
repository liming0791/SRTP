#ifndef MAINWINDOW_H

#define MAINWINDOW_H
#include <time.h>
#include <QMainWindow>
#include <QWidget>
#include <Qpainter>
#include <QTimer>
#include <QDateTime>
#include <QtGui>
#include <QtWidgets>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

class QTextEdit;

class QLabel;

class showWindow : public QWidget
{
	Q_OBJECT

	
public:
	showWindow(QWidget* parent);
	~showWindow();
	void showImage(cv::Mat img ,int& colorMode);

private:
	QLabel *label;
	QImage qImg;
};

class Detection : public QWidget
{
	Q_OBJECT

signals:
	void sendScreenShot();
	void toSetLabel(int i, QString);

private:
	cv::CascadeClassifier* face_cascade;

public:
	Detection(QWidget* parent);
	~Detection();
	bool detectFace(cv::Mat frame,double S, int N , int X, int Y);
	cv::Mat rgbHist(cv::Mat frame);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public slots:
	void setScaleFactor(double S);
	void setMinNeighbors(int N);
	void setMinX(int x);
	void setMinY(int y);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void setLabel(int i, QString str);
	void openCamera();
	void eachFrame();
	void beginFaceDetect();
	void beginScreenShot();
    int colorMode;
	cv::Mat frame;

private:
	//data for vedio
	
	
	cv::VideoCapture capture;
	QTimer* timer;

	//button actions
    QAction *openAction;
    QAction *saveAction;
	QAction *screenShotAction;
	QAction *stopAction;
	QAction *startCameraAction;
	QAction *detectFaceAction;
	
	//detecter
	Detection *detecter;

	//four windows
	showWindow *view1;
	showWindow *view2;
	showWindow *view3;
	showWindow *view4;

	//labels
	QLabel *attr1;
	QLabel *attr2;
	QLabel *attr3;
	QLabel *attr4;

	//judge
	bool ifDetectFace;
	bool ifDetectRGBHist;
	bool ifShot;

	//
	double S;
	int N; 
	int X;
	int Y;
	
};



#endif // MAINWINDOW_H
