#ifndef CMWFACEDETECTIONTAB_H
#define CMWFACEDETECTIONTAB_H

#include <QWidget>

class CGLWidget;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class CMWFaceDetectionTab : public QWidget
{
	Q_OBJECT

	public:
		CMWFaceDetectionTab(QWidget *parent = 0);

	signals:

	private slots:

	private:
		QPushButton	*mPbEnable;
		QHBoxLayout *mHbLayout;
		QVBoxLayout	*mVbLayout;
		CGLWidget	*mCGLWidget;
};

#endif
