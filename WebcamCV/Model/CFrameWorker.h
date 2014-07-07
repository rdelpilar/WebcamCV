#ifndef CFRAMEWORKER_H
#define CFRAMEWORKER_H

#include <opencv2\core\core.hpp>
#include <opencv2\core\mat.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <memory>

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include "..\Structures\CameraProperties.h"

class CFrameProcessorInterface;
class CFrameCapture;
class QImage;

typedef std::shared_ptr<QImage>						SHARED_QIMAGE;
typedef std::shared_ptr<CFrameCapture>				SHARED_FRAMCAP;
typedef std::shared_ptr<CFrameProcessorInterface>	SHARED_FRAMPROCINF;

class CFrameWorker : public QObject
{
	Q_OBJECT

	public:
		CFrameWorker(int deviceId = -1);
		~CFrameWorker();
		bool isPaused();
		void resume();

	signals:
		void processed(QImage &);
		void finished();

	public slots:
		void pause();
		void stop();
		void process();
		void setFrameProcessor(SHARED_FRAMPROCINF);

	private:
		bool				mPaused;
		bool				mStopped;
		QMutex				mMutex;
		QWaitCondition		mWaitCondition;
		cv::Mat				mMatIn;
		cv::Mat				mMatOut;
		SHARED_FRAMCAP		mFrameCapture;
		SHARED_FRAMPROCINF	mFrameProcessor;
};

#endif
