#ifndef CFACEDETECTIONFRAMEPROCESSOR_H
#define CFACEDETECTIONFRAMEPROCESSOR_H

#include <opencv2\core\core.hpp>
#include <opencv2\contrib\contrib.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "CFrameProcessorInterface.h"

#include <QDebug>

class CFaceDetectionFrameProcessor : public CFrameProcessorInterface
{
	public:
		CFaceDetectionFrameProcessor()
			:	mHaarCascade("Cascade\\haarcascade_frontalface_default.xml"),
				mCsv("Data\\csv_file.txt")
		{
			mNames.push_back("Brad Pitt");
			mNames.push_back("Psy");
			mNames.push_back("Ranel");

			try
			{
				readCSV(mCsv, mImages, mLabels);
			}
			catch(cv::Exception &e)
			{
				std::cerr << "Error opening file \"" << mCsv << "\". Reason: " << e.msg << std::endl;
				exit(1);
			}

			mImageWidth = mImages[0].cols;
			mImageHeight = mImages[0].rows;

			mModel = cv::createFisherFaceRecognizer();
			mModel->train(mImages, mLabels);
			mCascade.load(mHaarCascade);
		}

		~CFaceDetectionFrameProcessor() {}
		
		void processFrame(cv::Mat &input, cv::Mat &output)
		{
			cv::Mat original = input.clone();
			cvtColor(original, mGray, CV_BGR2GRAY);
			mCascade.detectMultiScale(output, mFaces, 1.13, 3, CV_HAAR_DO_CANNY_PRUNING, cv::Size(5, 5));

			if(mFaces.empty())
			{
				cv::resize(original, mGray, cv::Size(320, 240), 1.0, 1.0, cv::INTER_CUBIC);
				output = mGray.clone();
			}
			else
			{
				for(int i = 0; i < mFaces.size(); ++i)
				{
					if(mFaces[i].x < 0 ||
						mFaces[i].y < 0 ||
						mFaces[i].width < 0 ||
						mFaces[i].height < 0)
						continue;

					mRecti = mFaces[i];
					mFace = mGray(mRecti);
					cv::resize(mFace, mFaceResized, cv::Size(mImageWidth, mImageHeight), 1.0, 1.0, cv::INTER_CUBIC);
					mModel->predict(mFaceResized, mPredictedId, mConfidence);
					cv::rectangle(original, mRecti, CV_RGB(0, 255, 0), 1);

					qDebug() << "Predicted Id: " << mPredictedId;
					qDebug() << "Confidence Level: " << mConfidence;

					if(mPredictedId < 0 || mConfidence < 4000.0)
						mBoxText = "Unknown Person";
					else
						mBoxText = cv::format("%s: %d%%", mNames[mPredictedId].c_str(), (int) mConfidence/80);

					mPosX = std::max(mRecti.tl().x - 10, 0);
					mPosY = std::max(mRecti.tl().y - 10, 0);

					if(mPosX > 0 && mPosY > 0)
						cv::putText(original, mBoxText, cv::Point(mPosX, mPosY), cv::FONT_HERSHEY_PLAIN, 0.8, CV_RGB(0, 255, 0), 0.5);

					output = original.clone();
				}
			}
		}

	private:
		CFaceDetectionFrameProcessor(const CFaceDetectionFrameProcessor &);
		CFaceDetectionFrameProcessor &operator=(const CFaceDetectionFrameProcessor &);
		
		void readCSV(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';')
		{
			std::ifstream file(filename.c_str(), std::ifstream::in);
			
			if (!file)
			{
				std::string error_message = "No valid input file was given, please check the given filename.";
				CV_Error(CV_StsBadArg, error_message);
			}
			
			std::string line, path, classlabel;
			
			while (getline(file, line))
			{
				std::stringstream liness(line);
				getline(liness, path, separator);
				getline(liness, classlabel);
				
				if(!path.empty() && !classlabel.empty())
				{
					images.push_back(cv::imread(path, 0));
					labels.push_back(atoi(classlabel.c_str()));
				}
			}
		}

	private:
		std::string mHaarCascade;
		std::string mCsv;
		cv::CascadeClassifier mCascade;
		std::vector<cv::Rect> mFaces;
		std::vector<cv::Mat> mImages;
		std::vector<int> mLabels;
		std::vector<std::string> mNames;
		cv::Rect mRecti;
		cv::Mat mFace;
		cv::Mat mGray;
		cv::Mat mFaceResized;
		cv::Ptr<cv::FaceRecognizer> mModel;
		std::string mBoxText;
		int mPosX;
		int mPosY;
		int mImageWidth;
		int mImageHeight;
		int mPredictedId;
		double mConfidence;
		std::string sConf;
};

#endif
