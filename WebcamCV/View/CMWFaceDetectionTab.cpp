#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "CGLWidget.h"
#include "CMWFaceDetectionTab.h"
#include "..\Config\Config.h"

CMWFaceDetectionTab::CMWFaceDetectionTab(QWidget *parent)
	: QWidget(parent)
{
	mCGLWidget = new CGLWidget();
	mCGLWidget->setMinimumSize(MIN_FRAME_WIDTH, MIN_FRAME_HEIGHT);
	mCGLWidget->setMaximumSize(MIN_FRAME_WIDTH, MIN_FRAME_HEIGHT);
	mCGLWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	mPbEnable = new QPushButton(tr("Enable"));
	mPbEnable->setMinimumSize(DEF_PB_WIDTH, DEF_PB_HEIGHT);
	mPbEnable->setMaximumSize(DEF_PB_WIDTH, DEF_PB_HEIGHT);
	mPbEnable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	mHbLayout = new QHBoxLayout;
	mHbLayout->addWidget(mPbEnable);

	// Main layout.
	mVbLayout = new QVBoxLayout;
	mVbLayout->addWidget(mCGLWidget);
	mVbLayout->addStretch();
	mVbLayout->addLayout(mHbLayout);
	mVbLayout->addStretch();

	setLayout(mVbLayout);
}
