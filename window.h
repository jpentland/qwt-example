#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include <QBoxLayout>

#include <stdio.h>

// class definition 'Window'
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

public:
	Window(const char *fileName = NULL); 
	~Window();



	void timerEvent( QTimerEvent * );

public slots:
	void setGain(double gain);

// internal variables for the window class
private:
  // graphical elements from the Qwt library - http://qwt.sourceforge.net/annotated.html
	QwtKnob      knob;
	QwtThermo    thermo;
	QwtPlot      plot;
	QwtPlotCurve curve;

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  vLayout;  // vertical layout
	QHBoxLayout  hLayout;  // horizontal layout

	static const int plotDataSize = 100;

	// data arrays for the plot
	double xData[plotDataSize];
	double yData[plotDataSize];

	double gain;
	int count;

	// File for outputting text data
	FILE *outFile;
};

#endif // WINDOW_H
