#ifndef CDEVICEPROBER_H
#define CDEVICEPROBER_H

#include <memory>
#include <vector>
#include <string>
#include "..\Structures\CameraProperties.h"
#include "..\3rdparty\VideoInput\include\videoInput.h"

typedef std::vector<std::string> VECSTRING;

class CDeviceProber
{
	public:
		CDeviceProber();
		~CDeviceProber();
		int getDeviceCount() const;
		VECSTRING& getDeviceNames();
		bool isValidDeviceParams(CAMPROP &);
		void stopDevice(int &);

	private:
		std::shared_ptr<videoInput>		mVideoInput;
		VECSTRING						mDeviceNames;
		int								mNumDevices;
};

#endif
