#ifndef CMWLIVEFEEDTAB_H
#define CMWLIVEFEEDTAB_H

#include <QWidget>

class CGLWidget;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;

class CMWLiveFeedTab : public QWidget
{
	Q_OBJECT

	signals:

	public slots:

	public:
		CMWLiveFeedTab(QWidget *parent = 0);

	private:
		CGLWidget		*mCGLWidget;
		QPushButton		*mButtonCapture;
		QPushButton		*mButtonRecord;
		QVBoxLayout		*mVBLayout;
		QHBoxLayout		*mHBLayout;
};

#endif
