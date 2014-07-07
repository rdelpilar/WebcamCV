// Purpose: To capture frames from camera device.

#ifndef CFRAMECAPTURE_H
#define CFRAMECAPTURE_H

#include <memory>
#include "..\Structures\CameraProperties.h"
#include "..\3rdparty\VideoInput\include\videoInput.h"
#include "..\3rdparty\CDeviceProber.h"

class Mat;

typedef std::shared_ptr<videoInput>		SHARED_VIDINPUT;
typedef std::shared_ptr<CDeviceProber>	SHARED_DEVPROBER;
typedef std::vector<unsigned char>		VEC_UCHAR;

class CFrameCapture
{
	public:
		CFrameCapture(int deviceId = -1);
		~CFrameCapture();

		void setProperties(CAMPROP &);
		CAMPROP& getProperties();
		cv::Mat fetchNewFrame();

	private:
		SHARED_VIDINPUT		mVideoInput;
		SHARED_DEVPROBER	mDeviceProber;
		CAMPROP				mCamProp;
		VEC_UCHAR			mBuffer;
		cv::Mat				mImage;
};

#endif
