#include <QDebug>
#include "CDeviceProber.h"
#include "..\Config\Config.h"

CDeviceProber::CDeviceProber()
	: mVideoInput(std::make_shared<videoInput>())
{
	mVideoInput->setVerbose(false);
	mNumDevices	= mVideoInput->listDevices();
}

CDeviceProber::~CDeviceProber()
{

}

// Return the number of devices.
int CDeviceProber::getDeviceCount() const
{
	return mNumDevices;
}

// Return the string names of devices.
VECSTRING& CDeviceProber::getDeviceNames()
{
	// Get the string names of camera devices found.
	for(int i=0; i<mNumDevices; ++i) {
		std::string deviceName(mVideoInput->getDeviceName(i));
		mDeviceNames.push_back(deviceName);
	}

	return mDeviceNames;
}

// Checks if camProp has valid parameters.
bool CDeviceProber::isValidDeviceParams(CAMPROP &camprop)
{
	bool success = false;

	stopDevice(camprop.CAM_PROP_DEVICE_ID);

	// Set device frame width and height.
	mVideoInput->setupDevice(
		camprop.CAM_PROP_DEVICE_ID,
		camprop.CAM_PROP_FRAME_WIDTH,
		camprop.CAM_PROP_FRAME_HEIGHT
		);

	// Set device frame rate - return may not be always valid
	mVideoInput->setIdealFramerate(
		camprop.CAM_PROP_DEVICE_ID,
		camprop.CAM_PROP_FPS
		);

	camprop.CAM_PROP_SIZE = mVideoInput->getSize(camprop.CAM_PROP_DEVICE_ID);
	camprop.CAM_PROP_DEVICE_NAME = mVideoInput->getDeviceName(camprop.CAM_PROP_DEVICE_ID);

	if(camprop.CAM_PROP_FRAME_WIDTH > 0		||
		camprop.CAM_PROP_FRAME_HEIGHT > 0	||
		camprop.CAM_PROP_SIZE > 0)
	{		
		success = true;
	}
	
	return success;
}

void CDeviceProber::stopDevice(int &camId)
{
	mVideoInput->stopDevice(camId);
}
