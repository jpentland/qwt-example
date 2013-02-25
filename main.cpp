#include <window.h>

#include <QApplication>

int main(int argc, char *argv[])
{
	char *fileName = NULL;

	QApplication app(argc, argv);

	// Get filename argument
	if(argc > 1) {

		fileName = argv[1];
	}

	// create the window
	Window window(fileName);
	window.showMaximized();

	// call the window.timerEvent function every 40 ms
	window.startTimer(40);

	// execute the application
	return app.exec();
}
