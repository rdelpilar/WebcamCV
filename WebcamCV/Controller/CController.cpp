#include <opencv2\core\core.hpp>

#include <QObject>
#include <QThread>
#include <QImage>
#include <QMetaType>
#include <QDebug>
#include "CController.h"
#include "..\View\CMainWindow.h"
#include "..\3rdparty\CDeviceProber.h"
#include "..\Model\CFrameWorker.h"
#include "..\Model\CLiveFeedFrameProcessor.h"
#include "..\Model\CMotionDetectionFrameProcessor.h"
#include "..\Model\CFaceDetectionFrameProcessor.h"
#include "..\Config\Config.h"

CController::CController()
{

}

CController::CController(CMainWindow* _mainWindow)
	:	mLiveFeedFrameProc(std::make_shared<CLiveFeedFrameProcessor>()),
		mMotionDetectionFrameProc(std::make_shared<CMotionDetectionFrameProcessor>()),
		mFaceDetectionFrameProc(std::make_shared<CFaceDetectionFrameProcessor>())
{
	mMainWindow		= _mainWindow;
}

CController::~CController()
{

}

void CController::init()
{
	if(mDeviceCount > 0) {
		for(int i=0; i<mDeviceCount; ++i)
			createWorker(i);

		if(!mThreadCont.empty()) {
			SHARED_VECQTHREAD::const_iterator it = mThreadCont.begin();
			for(; it != mThreadCont.end(); ++it)
				it->get()->start(QThread::NormalPriority);
		}

		mWorkerCont.at(0)->resume();
	}
}

void CController::setupConnectors()
{
	//
}

void CController::setDeviceCount(int numDevices)
{
	mDeviceCount = numDevices;
}

bool CController::createWorker(int camId)
{
	auto mWorker = std::make_shared<CFrameWorker>(camId);
	mWorker->setFrameProcessor(mLiveFeedFrameProc);

	auto mThread = std::make_shared<QThread>();
	qRegisterMetaType<QImage>("QImage &");
	connect(mWorker.get(), SIGNAL(processed(QImage &)), mMainWindow, SLOT(displayImage(QImage &)));
	mWorker->moveToThread(mThread.get());
	
	connect(mThread.get(), SIGNAL(started()), mWorker.get(), SLOT(process()));

	mWorkerCont.push_back(mWorker);
	mThreadCont.push_back(mThread);

	return true;
}

int CController::getActiveWorker() const
{
	for(int i=0; i<mWorkerCont.size(); ++i) {
		if(!mWorkerCont.at(i).get()->isPaused())
			return i;
	}
}

////////////////// PUBLIC SLOTS

void CController::setFrameProcessor(int tabIndex)
{
	auto index = getActiveWorker();
	
	switch(tabIndex) {
		case LIVE_FEED			:	mWorkerCont.at(index).get()->setFrameProcessor(mLiveFeedFrameProc);
									break;

		case MOTION_DETECTION	:	mWorkerCont.at(index).get()->setFrameProcessor(mMotionDetectionFrameProc);
									break;

		case FACE_DETECTION		:	mWorkerCont.at(index).get()->setFrameProcessor(mFaceDetectionFrameProc);
									break;

		case INVALID			:	break;
		default					:	break;
	}
}

void CController::stopWorkers()
{
	SHARED_VECFRAMWORKER::const_iterator cit1 = mWorkerCont.begin();
	for(; cit1 != mWorkerCont.end(); ++cit1) {
		cit1->get()->stop();
		cit1->get()->resume();
	}

	SHARED_VECQTHREAD::const_iterator cit2 = mThreadCont.begin();
	for(; cit2 != mThreadCont.end(); ++cit2) {
		cit2->get()->exit();
	}
}
