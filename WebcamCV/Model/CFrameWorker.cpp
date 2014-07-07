#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\video\background_segm.hpp>
#include "CFrameWorker.h"
#include <QGLWidget>
#include <QDebug>
#include <vector>


#include "CFrameProcessorInterface.h"
#include "CFrameCapture.h"
#include "..\Config\Config.h"

CFrameWorker::CFrameWorker(int deviceId)
	:	mPaused(true),
		mStopped(false),
		mFrameCapture(std::make_shared<CFrameCapture>(deviceId)),
		mFrameProcessor(0),
		mMatIn(),
		mMatOut()

{
	
}

CFrameWorker::~CFrameWorker()
{

}

bool CFrameWorker::isPaused()
{
	mMutex.lock();
	auto result =  mPaused;
	mMutex.unlock();

	return result;
}

void CFrameWorker::pause()
{
	mMutex.lock();
	mPaused = true;
	mMutex.unlock();
}

void CFrameWorker::resume()
{
	mMutex.lock();
	mPaused = false;
	mWaitCondition.wakeOne();
	mMutex.unlock();
}

void CFrameWorker::stop()
{
	mMutex.lock();
	mStopped = true;
	mMutex.unlock();
}

void CFrameWorker::process()
{
	// Compute frame fetch interval in ms.
	auto interval = (int) (SECOND / mFrameCapture->getProperties().CAM_PROP_FPS);
	std::vector<std::vector<cv::Point> > contours;
	

	while(!mStopped) {

		mMutex.lock();
		if(mPaused)
			mWaitCondition.wait(&mMutex);
		mMutex.unlock();

		if(mStopped) break;

		mMatIn = mFrameCapture->fetchNewFrame();
		if(mMatIn.empty()) {
			qDebug() << "Error getting frame: Caller CFrameWorker";
			break;
		}

		if(mFrameProcessor) {
			mFrameProcessor->processFrame(mMatIn, mMatOut);				
				QImage mQimage((const unsigned char *) mMatOut.data,
														mMatOut.cols, 
														mMatOut.rows, 
														mMatOut.step, 
														QImage::Format_RGB888);
				mQimage = QGLWidget::convertToGLFormat(mQimage);
			Sleep(interval);
			emit processed(mQimage);
		}
	}

	mMutex.unlock();
}

void CFrameWorker::setFrameProcessor(SHARED_FRAMPROCINF processor)
{
	mFrameProcessor = processor;
}
