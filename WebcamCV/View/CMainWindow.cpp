#include <QWidget>
#include <QThread>
#include <QList>
#include <QImage>
#include <QTabWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QDebug>
#include "CMainWindow.h"
#include "CGLWidget.h"
#include "CMWLiveFeedTab.h"
#include "CMWMotionDetectionTab.h"
#include "CMWFaceDetectionTab.h"
#include "..\Controller\CController.h"
#include "..\3rdparty\CDeviceProber.h"
#include "..\Config\Config.h"

// Default constructor.
CMainWindow::CMainWindow(QWidget *parent, Qt::WFlags flags)
	:	QMainWindow(parent, flags),
		mDeviceProber(std::make_shared<CDeviceProber>())
{
	createWindow();
	createActions();
	createCGLWidgetList();

	auto deviceNames	= mDeviceProber->getDeviceNames();
	for(int i=0; i<deviceNames.size(); ++i)
		mDeviceProber->stopDevice(i);

	mDeviceProber.reset();
	if(!deviceNames.empty()) {
		std::vector<std::string>::const_iterator it;
		for(it = deviceNames.begin(); it != deviceNames.end(); ++it) {
			mCameraAction = new QAction(tr(it->c_str()), this);
			mCameraAction->setCheckable(true);
			mVecQaction.push_back(mCameraAction);
		}

		mVecQaction.front()->setChecked(true);

	} else {
		
		qDebug() << "No camera found.\n";
		std::shared_ptr<QImage> image = std::make_shared<QImage>("./Resources/notfound.jpg");
		mCameraAction = new QAction(tr("No device(s) found"), this);
		mCameraAction->setEnabled(false);
		mCMWLiveFeedTab->setEnabled(false);
		mCMWFaceDetectionTab->setEnabled(false);

	}

	createMenus();

	mController = CSingleton<CController>::getInstance(this);
	
	connect(mTabWidget, SIGNAL(currentChanged(int)), mController.get(), SLOT(setFrameProcessor(int)));
	connect(this, SIGNAL(destroyed()), mController.get(), SLOT(stopWorkers()));
	connect(mExitAction, SIGNAL(triggered()), mController.get(), SLOT(stopWorkers()));
	connect(mExitAction, SIGNAL(triggered()), this, SLOT(close()));

	mController->setDeviceCount(deviceNames.size());
	mController->init();
}

CMainWindow::~CMainWindow()
{

}

void CMainWindow::createWindow()
{
	// Set properties for main window.
	setWindowTitle(tr("WebcamCV"));
	setFixedSize(MIN_WIN_WIDTH, MIN_WIN_HEIGHT);
	mMWWidget = new QWidget(this);
	mMWWidget->setFixedSize(MIN_WIN_WIDTH, MIN_WIN_HEIGHT);
	setCentralWidget(mMWWidget);

	// Create tabs.
	mCMWLiveFeedTab = new CMWLiveFeedTab();
	mCMWMotionDetectionTab = new CMWMotionDetectionTab();
	mCMWFaceDetectionTab = new CMWFaceDetectionTab();
	
	// Create a new tab widget.
	mTabWidget = new QTabWidget(mMWWidget);

	// Add monitor tab to tab widget, set tab widget properties.
	mTabWidget->addTab(mCMWLiveFeedTab, tr("Monitor"));
	mTabWidget->addTab(mCMWMotionDetectionTab, tr("Motion Detection"));
	mTabWidget->addTab(mCMWFaceDetectionTab, tr("Face Recognizer"));
	mTabWidget->setGeometry(TAB_COORD_X, TAB_COORD_Y, MIN_TAB_WIDTH, MIN_TAB_HEIGHT);
	mTabWidget->setCurrentIndex(0);
}

void CMainWindow::createActions()
{
	mSettingsAction = new QAction(tr("&Settings"), this);
	mExitAction		= new QAction(tr("&Exit"), this);
	mAboutAction	= new QAction(tr("About"), this);
}

void CMainWindow::createMenus()
{
	mFileMenu	= menuBar()->addMenu(tr("&File"));
	mFileMenu->addAction(mSettingsAction);
	mFileMenu->addAction(mExitAction);

	mCameraMenu	= menuBar()->addMenu(tr("&Camera"));
	VEC_QACTION::const_iterator it = mVecQaction.begin();
	for(; it != mVecQaction.end(); ++it)
		mCameraMenu->addAction(*it);

	mHelpMenu	= menuBar()->addMenu(tr("&Help"));
	mHelpMenu->addAction(mAboutAction);
}

void CMainWindow::createCGLWidgetList()
{
	for(int i=0; i<mTabWidget->count(); ++i) {
		QWidget *qwidget = mTabWidget->widget(i);
		mCGLWidgetList.push_back(qwidget->findChild<CGLWidget *>());
	}
}

void CMainWindow::setCurrentTabIndex(int)
{

}

int CMainWindow::getCurrentTabIndex() const
{
	return mTabWidget->currentIndex();
}


void CMainWindow::displayImage(QImage &img)
{
	if(!img.isNull()) {
		mCGLWidget = mCGLWidgetList[mTabWidget->currentIndex()];
		mCGLWidget->sendImage(img);
	}
}
