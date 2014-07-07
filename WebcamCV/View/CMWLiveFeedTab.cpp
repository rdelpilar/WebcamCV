#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "CGLWidget.h"
#include "CMWLiveFeedTab.h"
#include "..\Config\Config.h"

CMWLiveFeedTab::CMWLiveFeedTab(QWidget *parent)
	: QWidget(parent)
{
	mCGLWidget = new CGLWidget();
	mCGLWidget->setMinimumSize(MIN_FRAME_WIDTH, MIN_FRAME_HEIGHT);
	mCGLWidget->setMaximumSize(MIN_FRAME_WIDTH, MIN_FRAME_HEIGHT);
	mCGLWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	// Capture button.
	mButtonCapture = new QPushButton(tr("Capture"));
	mButtonCapture->setMinimumSize(DEF_PB_WIDTH, DEF_PB_HEIGHT);
	mButtonCapture->setMaximumSize(DEF_PB_WIDTH, DEF_PB_HEIGHT);
	mButtonCapture->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	// Record button.
	mButtonRecord = new QPushButton(tr("Record"));
	mButtonRecord->setMinimumSize(DEF_PB_WIDTH, DEF_PB_HEIGHT);
	mButtonRecord->setMaximumSize(DEF_PB_WIDTH, DEF_PB_HEIGHT);
	mButtonRecord->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	// Horizontal box layout for push buttons.
	mHBLayout = new QHBoxLayout;
	mHBLayout->addWidget(mButtonCapture);
	mHBLayout->addWidget(mButtonRecord);

	// Main layout.
	mVBLayout = new QVBoxLayout;
	mVBLayout->addWidget(mCGLWidget);
	mVBLayout->addStretch();
	mVBLayout->addLayout(mHBLayout);
	mVBLayout->addStretch();

	setLayout(mVBLayout);
}
