#ifndef CCONTROLLER_H
#define CCONTROLLER_H

#include <memory>
#include <vector>
#include <string>
#include <QObject>
#include "..\Structures\CameraProperties.h"

class CDeviceProber;
class CFrameWorker;
class CLiveFeedFrameProcessor;
class CMotionDetectionFrameProcessor;
class CFaceDetectionFrameProcessor;
class CMainWindow;
class QThread;
class QImage;

typedef std::vector<std::shared_ptr<QThread>>			SHARED_VECQTHREAD;
typedef std::vector<std::shared_ptr<CFrameWorker>>		SHARED_VECFRAMWORKER;
typedef std::shared_ptr<CLiveFeedFrameProcessor>		SHARED_LIVFEEDPROC;
typedef std::shared_ptr<CMotionDetectionFrameProcessor>	SHARED_MOTDETPROC;
typedef std::shared_ptr<CFaceDetectionFrameProcessor>	SHARED_FACEDETPROC;
typedef std::shared_ptr<QImage>							SHARED_QIMAGE;

class CController : public QObject
{
	Q_OBJECT

	public:
		CController();
		CController(CMainWindow *);
		~CController();
		void setDeviceCount(int);
		void init();

	public slots:
		void setFrameProcessor(int);
		void stopWorkers();

	private:
		void setupConnectors();
		bool createWorker(int);
		int getActiveWorker() const;

	private:
		CMainWindow				*mMainWindow;		
		SHARED_VECQTHREAD		mThreadCont;
		SHARED_VECFRAMWORKER	mWorkerCont;
		SHARED_LIVFEEDPROC		mLiveFeedFrameProc;
		SHARED_MOTDETPROC		mMotionDetectionFrameProc;
		SHARED_FACEDETPROC		mFaceDetectionFrameProc;

		int						mDeviceCount;
};

#endif
