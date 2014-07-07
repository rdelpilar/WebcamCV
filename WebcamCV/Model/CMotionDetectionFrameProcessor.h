#ifndef CMOTIONDETECTIONFRAMEPROCESSOR_H
#define CMOTIONDETECTIONFRAMEPROCESSOR_H

#include <opencv2\core\mat.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\background_segm.hpp>
#include <memory>
#include <vector>
#include "CFrameProcessorInterface.h"

typedef std::shared_ptr<cv::BackgroundSubtractorMOG2>	SHARED_BGSMOG2;
typedef std::vector<std::vector<cv::Point>>				VEC_POINT;

class CMotionDetectionFrameProcessor : public CFrameProcessorInterface
{
	public:
		CMotionDetectionFrameProcessor()
			:	mMog2(std::make_shared<cv::BackgroundSubtractorMOG2>(30, 4, false))
				{ mMog2->set("nmixtures", 3); }
		~CMotionDetectionFrameProcessor() {}
		void processFrame(cv::Mat &input, cv::Mat &output)
		{
			mMog2->operator()(input, output, 0.01);
			cv::erode(output, output, cv::Mat());
			cv::dilate(output, output, cv::Mat());
			cv::findContours(output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
			cv::drawContours(input, contours, -1, cv::Scalar(0, 255, 0),1);
			output = input.clone();
		}

	private:
		CMotionDetectionFrameProcessor(const CMotionDetectionFrameProcessor &);
		CMotionDetectionFrameProcessor &operator=(const CMotionDetectionFrameProcessor &);

	private:
		SHARED_BGSMOG2	mMog2;
		VEC_POINT		contours;
};

#endif
