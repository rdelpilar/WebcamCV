#include <memory>
#include <QtGui/QApplication>
#include <QtGui/QSplashScreen>
#include <QtGui/Qpixmap>
#include "View/CMainWindow.h"

int main(int argc, char *argv[])
{
	QApplication	app(argc, argv);

	QPixmap pixmap("./Resources/splash.jpg");
	std::shared_ptr<QSplashScreen> 
		splashScreen = std::make_shared<QSplashScreen>(pixmap);
	
	splashScreen->show();
	splashScreen->showMessage("Searching for devices...", 
		Qt::AlignBottom, Qt::white);

	std::shared_ptr<CMainWindow> mainWindow = std::make_shared<CMainWindow>();
	splashScreen->finish(mainWindow.get());

	mainWindow->setAttribute(Qt::WA_QuitOnClose);
	mainWindow->show();

	return app.exec();
}
