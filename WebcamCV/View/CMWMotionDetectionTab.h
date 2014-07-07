#ifndef CMWMOTIONDETECTIONTAB_H
#define CMWMOTIONDETECTIONTAB_H

#include <QWidget>

class CGLWidget;
class QLabel;
class QGroupBox;
class QSlider;
class QLineEdit;
class QPushButton;
class QCheckBox;
class QHBoxLayout;
class QVBoxLayout;

class CMWMotionDetectionTab : public QWidget
{
	Q_OBJECT

	public:
		CMWMotionDetectionTab(QWidget *parent = 0);

	signals:

	private slots:
		void updateLineEditPercent(int);

	private:
		QGroupBox	*mGroupBox;
		QSlider		*mSlider;
		QLineEdit	*mLineEdit;
		QLabel		*mLabelPercent;
		QPushButton	*mPbEnable;
		QCheckBox	*mCheckBox;
		QHBoxLayout	*mHblGroupBox;
		QHBoxLayout *mHblgbpb;
		QVBoxLayout	*mVbLayout;
		CGLWidget	*mCGLWidget;
};

#endif
