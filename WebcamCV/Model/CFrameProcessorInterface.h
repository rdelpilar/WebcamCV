// Interface for frame processing algorithms.
// done

#ifndef CFRAMEPROCESSORINTERFACE_H
#define CFRAMEPROCESSORINTERFACE_H

#include <memory>

class Mat;

class CFrameProcessorInterface
{
public:
	CFrameProcessorInterface() {}
	virtual ~CFrameProcessorInterface() {}
	virtual void processFrame(cv::Mat &, cv::Mat &) = 0;
};

#endif
