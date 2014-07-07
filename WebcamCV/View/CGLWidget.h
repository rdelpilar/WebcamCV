#ifndef CGLWIDGET_H
#define CGLWIDGET_H

#include <memory>
#include <QGLWidget>
#include <QImage>

class CGLWidget : public QGLWidget
{
	Q_OBJECT

	public:
		CGLWidget(QWidget *parent = NULL);
		~CGLWidget();
		void sendImage(QImage &);

	protected:
		void initializeGL();
		void resizeGL(int, int);
		void paintGL();

	private:
		QImage mImage;
};

#endif
