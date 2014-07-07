#include <opencv2\core\core.hpp>
#include "CFrameCapture.h"
#include "..\Config\Config.h"
#include <QDebug>

CFrameCapture::CFrameCapture(int deviceId)
	:	mDeviceProber(std::make_shared<CDeviceProber>())
{
	if(deviceId < 0)
		return;

	// Set default parameters.
	mCamProp.CAM_PROP_DEVICE_ID		= deviceId;
	mCamProp.CAM_PROP_FRAME_WIDTH	= CAM_PROP_WIDTH_320;
	mCamProp.CAM_PROP_FRAME_HEIGHT	= CAM_PROP_HEIGHT_240;
	mCamProp.CAM_PROP_FPS			= CAM_PROP_FPS_60;

	// Check if above device parameters are valid.
	// Need to redo. Inefficient. Multiple calls to VideoInput.
	if(mDeviceProber->isValidDeviceParams(mCamProp)) {

		// Stop the device first.
		mDeviceProber->stopDevice(mCamProp.CAM_PROP_DEVICE_ID);

		// Create a new instance of VideoInput.
		mVideoInput = std::make_shared<videoInput>();

		// Setup ideal framerate.
		mVideoInput->setIdealFramerate(mCamProp.CAM_PROP_DEVICE_ID,
										mCamProp.CAM_PROP_FPS);

		// Setup device.
		mVideoInput->setupDevice(mCamProp.CAM_PROP_DEVICE_ID,
									mCamProp.CAM_PROP_FRAME_WIDTH,
									mCamProp.CAM_PROP_FRAME_HEIGHT);

		// Create a new buffer.
		mBuffer.reserve(mCamProp.CAM_PROP_SIZE);
	}
}

CFrameCapture::~CFrameCapture()
{

}

cv::Mat CFrameCapture::fetchNewFrame()
{
	
	bool success = mVideoInput->getPixels(mCamProp.CAM_PROP_DEVICE_ID, mBuffer.data(), true, true);
	if(success)
	{
		cv::Mat img((int) mCamProp.CAM_PROP_FRAME_HEIGHT, (int) mCamProp.CAM_PROP_FRAME_WIDTH, CV_8UC3, mBuffer.data());
		return img;
	}
	else
	{
		cv::Mat img;
		return img;
	}
}

void CFrameCapture::setProperties(CAMPROP &camProp)
{
	// Set camera properties
}

CAMPROP& CFrameCapture::getProperties()
{
	return mCamProp;
}