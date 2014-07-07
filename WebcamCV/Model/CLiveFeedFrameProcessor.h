#ifndef CLIVEFEEDFRAMEPROCESSOR_H
#define CLIVEFEEDFRAMEPROCESSOR_H

#include <opencv2\core\mat.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <memory>
#include "CFrameProcessorInterface.h"

class CLiveFeedFrameProcessor : public CFrameProcessorInterface
{
	public:
		CLiveFeedFrameProcessor() {}
		~CLiveFeedFrameProcessor() {}

		void processFrame(cv::Mat &input, cv::Mat &output)
		{
			output = input.clone();
		}

	private:
		CLiveFeedFrameProcessor(const CLiveFeedFrameProcessor &);
		CLiveFeedFrameProcessor &operator=(const CLiveFeedFrameProcessor &);
};

#endif
