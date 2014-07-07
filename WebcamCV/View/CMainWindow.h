#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <memory>
#include <QObject>
#include <QtGui\QMainWindow>
#include "..\Model\CSingleton.h"
#include "..\Config\Config.h"
#include "..\Structures\CameraProperties.h"

class QThread;
class QWidget;
class QTabWidget;
class QImage;
class CMWLiveFeedTab;
class CMWMotionDetectionTab;
class CMWFaceDetectionTab;
class CGLWidget;
class QAction;
class QMenu;
class CDeviceProber;
class CController;

typedef std::shared_ptr<CController>		SHARED_CNTRLR;
typedef std::shared_ptr<CDeviceProber>		SHARED_DEVPROBER;
typedef std::vector<QAction *>				VEC_QACTION;

class CMainWindow : public QMainWindow, 
					public std::enable_shared_from_this<CMainWindow>
{
	Q_OBJECT

public:
	CMainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~CMainWindow();

public slots:
	void setCurrentTabIndex(int);
	int getCurrentTabIndex() const;
	void displayImage(QImage &);

private:
	void createWindow();
	void createActions();
	void createCGLWidgetList();
	void createMenus();

private:

	QWidget					*mMWWidget;
	QTabWidget				*mTabWidget;
	CMWLiveFeedTab			*mCMWLiveFeedTab;
	CMWMotionDetectionTab	*mCMWMotionDetectionTab;
	CMWFaceDetectionTab		*mCMWFaceDetectionTab;

	CGLWidget				*mCGLWidget;
	QList<CGLWidget *>		mCGLWidgetList;
	QMenu					*mFileMenu;
	QMenu					*mCameraMenu;
	QMenu					*mHelpMenu;

	QAction					*mSettingsAction;
	QAction					*mExitAction;
	QAction					*mCameraAction;
	QAction					*mAboutAction;

	VEC_QACTION				mVecQaction;
	SHARED_CNTRLR			mController;
	SHARED_DEVPROBER		mDeviceProber;
};

#endif
