#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <time.h>
#include <QMainWindow>
#include <QWidget>
#include <Qpainter>
#include <QTimer>
#include <QDateTime>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

class QTextEdit;

class QLabel;

class showWindow : public QWidget
{
	Q_OBJECT

signals:
	void sendScreenShot(cv::Mat& screenShot);
	void toSetLabel(int i, QString);

public slots:
	void setScaleFactor(double S);
	void setMinNeighbors(int N);
	void setMinX(int x);
	void setMinY(int y);
	
public:
	showWindow(QWidget* parent);
	~showWindow();
	void showImage(cv::Mat& img );
	void showAgainImage(cv::Mat& img);
	void showVedio(cv::VideoCapture cap);
	void showFrame();
	void screenShot();
	void stopVideo();
	void showScreenShot(cv::Mat& screenShot);
	void loadCamera();
	void detectAndDisplay();
	
//protected:
	//void:paintEvent(QPaintEvent *e);

private:
	cv::Mat frame;
	cv::VideoCapture capture;
	int ifShot;
	QTimer* timer;
	QTimer* timer2;
	int rgb;
	std::string face_cascade_name ;
	double scaleFactor;
	int minNeighbors; 
	int minX;
	int minY;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void setLabel(int i, QString str);

private slots:
    void openFile();
    void saveFile();
    
private:

	//QLabel *attr1;
    QAction *openAction;
    QAction *saveAction;
	QAction *screenShotAction;
	QAction *stopAction;
	QAction *startCameraAction;

	showWindow *view1;
	showWindow *view2;
	showWindow *view3;
	showWindow *view4;
	QLabel *attr1;
	QLabel *attr2;
	QLabel *attr3;
	QLabel *attr4;
	
    QTextEdit *textEdit;
};




#endif // MAINWINDOW_H
