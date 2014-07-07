#include <QLabel>
#include <QGroupBox>
#include <QSlider>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CGLWidget.h"
#include "CMWMotionDetectionTab.h"
#include "..\Config\Config.h"

CMWMotionDetectionTab::CMWMotionDetectionTab(QWidget *parent)
	:	QWidget(parent)
{
	// GLWidget for displaying frames.
	mCGLWidget = new CGLWidget();
	mCGLWidget->setMinimumSize(MIN_FRAME_WIDTH, MIN_FRAME_HEIGHT);
	mCGLWidget->setMaximumSize(MIN_FRAME_WIDTH, MIN_FRAME_HEIGHT);
	mCGLWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	// Group box
	mGroupBox = new QGroupBox(tr("Sensitivity"));

	// Slider
	mSlider = new QSlider;
	mSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	mSlider->setOrientation(Qt::Horizontal);
	mSlider->setTickPosition(QSlider::TicksBelow);

	// Line edit
	mLineEdit = new QLineEdit;
	mLineEdit->setMinimumSize(MIN_LINE_EDIT_WIDTH, MIN_LINE_EDIT_HEIGHT);
	mLineEdit->setMaximumSize(MIN_LINE_EDIT_WIDTH, MIN_LINE_EDIT_HEIGHT);
	mLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	mLineEdit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	mLineEdit->setInputMask("99.9");
	mLineEdit->setFrame(true);
	mLineEdit->setReadOnly(true);

	// Percent label
	mLabelPercent = new QLabel(tr("%"));
	mLabelPercent->setMinimumSize(MIN_LABEL_WIDTH, MIN_LABEL_HEIGHT);
	mLabelPercent->setMaximumSize(MIN_LABEL_WIDTH, MIN_LABEL_HEIGHT);
	mLabelPercent->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	// Layout for GroupBox, QSlider, QLineEdit, QLabel
	mHblGroupBox = new QHBoxLayout;
	mHblGroupBox->addWidget(mSlider);
	mHblGroupBox->addWidget(mLineEdit);
	mHblGroupBox->addWidget(mLabelPercent);

	mGroupBox->setLayout(mHblGroupBox);

	mPbEnable = new QPushButton(tr("Enable"));
	mPbEnable->setMinimumSize(DEF_PB_WIDTH, DEF_PB_HEIGHT);
	mPbEnable->setMaximumSize(DEF_PB_WIDTH, DEF_PB_HEIGHT);
	mPbEnable->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	mPbEnable->setDefault(true);

	mHblgbpb = new QHBoxLayout;
	mHblgbpb->addWidget(mGroupBox);
	mHblgbpb->addWidget(mPbEnable);

	// Binary image check box
	mCheckBox = new QCheckBox;
	mCheckBox->setMinimumHeight(MIN_CHECKBOX_HEIGHT);
	//m_checkbox->setMaximumHeight(20);
	mCheckBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	mCheckBox->setText(tr("Show Binary Image"));

	// Main layout
	mVbLayout = new QVBoxLayout;
	mVbLayout->setSpacing(DEF_LAYOUT_SPACING);
	mVbLayout->addWidget(mCGLWidget);
	mVbLayout->addLayout(mHblgbpb);
	mVbLayout->addStretch();
	mVbLayout->addWidget(mCheckBox);

	setLayout(mVbLayout);

	connect(mSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateLineEditPercent(int)));
}

void CMWMotionDetectionTab::updateLineEditPercent(int num)
{
	mLineEdit->setText(QString::number(num));
}