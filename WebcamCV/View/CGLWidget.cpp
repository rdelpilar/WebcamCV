#include <QtOpenGL\qgl.h>
#include <QDebug>

#include "..\View\CGLWidget.h"

CGLWidget::CGLWidget(QWidget *parent)
	:	QGLWidget(parent),
		mImage()
{

}

CGLWidget::~CGLWidget()
{

}


void CGLWidget::initializeGL()
{
	glViewport(0, 0, this->width(), this->height());
	qDebug() << "this->width(): " << this->width();
	qDebug() << "this->height(): " << this->height();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-this->width()/2, this->width()/2, this->height()/2, -this->height()/2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void CGLWidget::resizeGL(int x, int y)
{
	/*... */
}

void CGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(mImage.width(), mImage.height(), GL_RGBA, GL_UNSIGNED_BYTE, mImage.bits());
	glFlush();
}

void CGLWidget::sendImage(QImage &image)
{
	mImage = image;
	updateGL();
}
