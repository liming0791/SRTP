#include <QtGui>
#include <QtWidgets>
#include "platform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{	
	//init a window to apply layout
	QWidget* window = new QWidget(this);

	//init a detecter
	detecter = new Detection(this);



	//init four window to show result
	view1 = new showWindow(window);
	view2 = new showWindow(window);
	view3 = new showWindow(window);
	view4 = new showWindow(window);

	//init buttons
    //openAction = new QAction(QIcon(":/images/file-open"), tr("&Open..."), this);
    //openAction->setShortcuts(QKeySequence::Open);
    //openAction->setStatusTip(tr("Open an existing file"));
    //connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    /*saveAction = new QAction(QIcon(":/images/file-save"), tr("&Save..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a new file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);*/

	startCameraAction = new QAction(tr("&Startcamera..."),this);
	startCameraAction->setStatusTip(tr("Startfromcamera"));
	connect(startCameraAction, &QAction::triggered, this, &MainWindow::openCamera);

	detectFaceAction = new QAction(tr("&Detectface..."),this);
	detectFaceAction->setStatusTip(tr("Start to detect face"));
    connect(detectFaceAction, &QAction::triggered, this, &MainWindow::beginFaceDetect);

	screenShotAction = new QAction(tr("&Screenshot..."), this);
	screenShotAction->setStatusTip(tr("Take a screenshot and save the picture"));
    connect(screenShotAction, &QAction::triggered, this, &MainWindow::beginScreenShot);

	//stopAction = new QAction(tr("&Stop..."),this);
	//stopAction -> setStatusTip(tr("Stop the video"));
	//connect(stopAction, &QAction::triggered, view1, &Window::stopVideo);

	////init menue
 //   QMenu *file = menuBar()->addMenu(tr("&File"));
 //   file->addAction(openAction);
 //   file->addAction(saveAction);
	//file->addAction(screenShotAction);
	//file->addAction(stopAction);
	
	//init toolbar
    QToolBar *toolBar = addToolBar(tr("&File"));
    //toolBar->addAction(openAction);
    //toolBar->addAction(saveAction);
	toolBar->addAction(startCameraAction);
	toolBar->addAction(detectFaceAction);
	toolBar->addAction(screenShotAction);

	//init labels
	attr1 = new QLabel(tr("attr"));
	attr2 = new QLabel(tr("attr"));
	attr3 = new QLabel(tr("attr"));
	attr4 = new QLabel(tr("attr"));

	//init input boxes
	QDoubleSpinBox* input1 = new QDoubleSpinBox();
	input1->setMaximumWidth(50);
	QSpinBox* input2 = new QSpinBox();
	input2->setMaximumWidth(50);
	QSpinBox* input3 = new QSpinBox();
	input3->setMaximumWidth(50);
	QSpinBox* input4 = new QSpinBox();
	input4->setMaximumWidth(50);
	
	//left form layout
	QFormLayout* form = new QFormLayout();
	form->addRow("ScaleFactor",input1);
	form->addRow("MinNeighbors",input2);
	form->addRow("MinX",input3);
	form->addRow("MinY",input4);
	form->addRow(attr1);
	form->addRow(attr2);
	form->addRow(attr3);
	form->addRow(attr4);
	
	//init a widget to hold the form
	QWidget* widgetForm = new QWidget();
	widgetForm->setLayout(form);
	widgetForm->setMaximumWidth(120);

	//the main grid layout
	QGridLayout *mainLayout = new QGridLayout();
	mainLayout ->addWidget(widgetForm,0,0,2,1);
	mainLayout ->addWidget(view1,0,1,1,1);
	mainLayout ->addWidget(view2,0,2,1,1);
	mainLayout ->addWidget(view3,1,1,1,1);
	mainLayout ->addWidget(view4,1,2,1,1);
	

	//apply the layout
    this->setCentralWidget(window);
	this->centralWidget()->setLayout(mainLayout);

	//init timer
	timer=new QTimer(this);

	//connect for signals and slots
	connect(detecter,&Detection::sendScreenShot,this,&MainWindow::beginScreenShot);
	connect(input1,SIGNAL(valueChanged(double)),this,SLOT(setScaleFactor(double)));
	connect(input2,SIGNAL(valueChanged(int)),this,SLOT(setMinNeighbors(int)));
	connect(input3,SIGNAL(valueChanged(int)),this,SLOT(setMinX(int)));
	connect(input4,SIGNAL(valueChanged(int)),this,SLOT(setMinY(int)));
	connect(detecter,&Detection::toSetLabel,this,&MainWindow::setLabel);
	connect(timer,&QTimer::timeout,this,&MainWindow::eachFrame);
	//set bool
	ifDetectFace = false;
	ifDetectRGBHist = ifShot = false;

}

MainWindow::~MainWindow()
{
	delete timer;
	/*delete openAction;
	delete saveAction;
	delete screenShotAction;
	delete stopAction;
	delete startCameraAction;
	delete detectFaceAction;*/
	delete detecter;
	delete view1;
	delete view2;
	delete view3;
	delete view4;
	delete attr1;
	delete attr2;
	delete attr3;
	delete attr4;

}

//void MainWindow::openFile()
//{
//    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("avi file(*.avi)"));
//    if(!path.isEmpty()) {
//        /*QFile file(path);
//        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//            QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
//            return;*/
//		capture = cv::VideoCapture(path.toStdString());
//		if(capture.isOpened())
//			playVedio(capture);
//		else
//			QMessageBox::warning(this, tr("Open vedio failed"), tr("fail to open the vedio."));
//		
//			//view1->showImage(img);
//        }
//    else {
//        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
//    }
//}

void MainWindow::openCamera()
{
	detecter->loadCamera();
	timer->start(1000/60);
}

void MainWindow::eachFrame()
{
	detecter->queryFrame();
	//frame.copyTo(frame2);
	//frame2 = frame.clone();
	
	if(ifShot)
	{	 
		view2->showImage(detecter->getPic());

		QDateTime time = QDateTime::currentDateTime();  
		QString filename = time.toString("yyyy-MM-dd hh-mm-ss");
		cv::imwrite("screenshot"+filename.toStdString()+".png",detecter->getPic());

		ifShot = false;
	}

	if(ifDetectFace)
	{
		detecter->detectFace();
		view1->showImage(detecter->getPic());
	}
	else
	{
		view1->showImage(detecter->getPic());
	}

	if(ifDetectRGBHist)
	{

	}

	if(ifShot)
	{	 
		view2->showImage(detecter->getPic());

		QDateTime time = QDateTime::currentDateTime();  
		QString filename = time.toString("yyyy-MM-dd hh-mm-ss");
		cv::imwrite("screenshot"+filename.toStdString()+".png",detecter->getPic());

		ifShot = false;
	}
}


//void MainWindow::saveFile()
//{
//    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.txt)"));
//    if(!path.isEmpty()) {
//        QFile file(path);
//        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//            QMessageBox::warning(this, tr("Write File"), tr("Cannot open file:\n%1").arg(path));
//            return;
//        }
//        QTextStream out(&file);
//        out << textEdit->toPlainText();
//        file.close();
//    } else {
//        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
//    }
//}

void MainWindow::setLabel(int i , QString str)
{
	switch(i)
	{
	case 1: attr1->setText(str);attr1->show();break;
	case 2: attr2->setText(str);attr2->show();break;
	case 3: attr3->setText(str);attr3->show();break;
	case 4: attr4->setText(str);attr4->show();break;
	}
}

void MainWindow::beginFaceDetect()
{
	ifDetectFace = !ifDetectFace;
}

void MainWindow::beginScreenShot()
{
	ifShot = true;
}

void MainWindow::setScaleFactor(double S)
{
	S = S;

	
}

void MainWindow::setMinNeighbors(int N)
{
	N = N;
	
}

void MainWindow::setMinX(int X)
{
	X = X; 
	
}

void MainWindow::setMinY(int Y)
{
	Y = Y;
	
}

