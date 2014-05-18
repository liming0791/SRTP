#include <QtGui>
#include <QtWidgets>
#include "platform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{	
	QWidget* window = new QWidget(this);

	

	view1 = new showWindow(window);
	view2 = new showWindow(window);
	view3 = new showWindow(window);
	view4 = new showWindow(window);

    openAction = new QAction(QIcon(":/images/file-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    saveAction = new QAction(QIcon(":/images/file-save"), tr("&Save..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a new file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

	startCameraAction = new QAction(tr("&Startcamera..."),this);
	startCameraAction->setStatusTip(tr("Startfromcamera"));
	connect(startCameraAction, &QAction::triggered, view1, &showWindow::loadCamera);

	screenShotAction = new QAction(tr("&Screenshot..."), this);
	screenShotAction->setStatusTip(tr("Take a screenshot and save the picture"));
    connect(screenShotAction, &QAction::triggered, view1, &showWindow::screenShot);

	stopAction = new QAction(tr("&Stop..."),this);
	stopAction -> setStatusTip(tr("Stop the video"));
	connect(stopAction, &QAction::triggered, view1, &showWindow::stopVideo);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);
	file->addAction(screenShotAction);
	file->addAction(stopAction);
	
    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
	toolBar->addAction(startCameraAction);
	toolBar->addAction(screenShotAction);
	toolBar->addAction(stopAction);

	

	attr1 = new QLabel(tr("attr"));
	attr2 = new QLabel(tr("attr"));
	attr3 = new QLabel(tr("attr"));
	attr4 = new QLabel(tr("attr"));

	QDoubleSpinBox* input1 = new QDoubleSpinBox();
	input1->setMaximumWidth(50);
	QSpinBox* input2 = new QSpinBox();
	input2->setMaximumWidth(50);
	QSpinBox* input3 = new QSpinBox();
	input3->setMaximumWidth(50);
	QSpinBox* input4 = new QSpinBox();
	input4->setMaximumWidth(50);
	//QLineEdit* input5 = new QLineEdit();
	//input5->setMaximumWidth(30);

	/*QHBoxLayout* rightLayout3_1 = new QHBoxLayout();
	rightLayout3_1->addWidget(attr1);
	rightLayout3_1->addWidget(input1);

	QHBoxLayout* rightLayout3_2 = new QHBoxLayout();
	rightLayout3_1->addWidget(attr2);
	rightLayout3_1->addWidget(input2);

	QHBoxLayout* rightLayout3_3 = new QHBoxLayout();
	rightLayout3_1->addWidget(attr3);
	rightLayout3_1->addWidget(input3);

	QHBoxLayout* rightLayout3_4 = new QHBoxLayout();
	rightLayout3_1->addWidget(attr4);
	rightLayout3_1->addWidget(input4);

	QHBoxLayout* rightLayout3_5 = new QHBoxLayout();
	rightLayout3_1->addWidget(attr5);
	rightLayout3_1->addWidget(input5);*/

	/*QVBoxLayout* form = new QVBoxLayout();
	form->addWidget(input1);
	form->addWidget(input2);
	form->addWidget(input3);
	form->addWidget(input4);
	form->addWidget(input5);*/

	QFormLayout* form = new QFormLayout();
	form->addRow("ScaleFactor",input1);
	form->addRow("MinNeighbors",input2);
	form->addRow("MinX",input3);
	form->addRow("MinY",input4);
	form->addRow(attr1);
	form->addRow(attr2);
	form->addRow(attr3);
	form->addRow(attr4);
	//form->addRow("attr",input5);
	//rightLayout2->addWidget(attr5);

	QWidget* widgetForm = new QWidget();
	widgetForm->setLayout(form);
	widgetForm->setMaximumWidth(120);

	QGridLayout *mainLayout = new QGridLayout();
	mainLayout ->addWidget(widgetForm,0,0,2,1);
	mainLayout ->addWidget(view1,0,1,1,1);
	mainLayout ->addWidget(view2,0,2,1,1);
	mainLayout ->addWidget(view3,1,1,1,1);
	mainLayout ->addWidget(view4,1,2,1,1);
	

	//QHBoxLayout *mainLayout = new QHBoxLayout();
	//mainLayout->addLayout(leftLayout2);
	//mainLayout->addLayout(form);

    //textEdit = new QTextEdit(this);
	//window.setLayout(mainLayout);
    this->setCentralWidget(window);
	//window.show();
	this->centralWidget()->setLayout(mainLayout);

	connect(view1,&showWindow::sendScreenShot,view2,&showWindow::showScreenShot);
	connect(input1,SIGNAL(valueChanged(double)),view1,SLOT(setScaleFactor(double)));
	connect(input2,SIGNAL(valueChanged(int)),view1,SLOT(setMinNeighbors(int)));
	connect(input3,SIGNAL(valueChanged(int)),view1,SLOT(setMinX(int)));
	connect(input4,SIGNAL(valueChanged(int)),view1,SLOT(setMinY(int)));
	connect(view1,&showWindow::toSetLabel,this,&MainWindow::setLabel);

}

MainWindow::~MainWindow()
{
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("avi file(*.avi)"));
    if(!path.isEmpty()) {
        /*QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
            return;*/
		cv::VideoCapture capture(path.toStdString());
		if(capture.isOpened())
			view1->showVedio(capture);
		else
			QMessageBox::warning(this, tr("Open vedio failed"), tr("fail to open the vedio."));
		
			//view1->showImage(img);
        }
    else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

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