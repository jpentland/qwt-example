#include "window.h"
#include "adc.h"
#include "ledout.h"

Window::Window() 
	: plot( QString("Volumeter - Volume Graph")), 
	  gain(5), 
	  count(0) 
{
	// set up the gain knob
	knob.setValue(gain);

	// use the Qt signals/slots framework to update the gain -
	// every time the knob is moved, the setGain function will be called
	connect( &knob, SIGNAL(valueChanged(double)), SLOT(setGain(double)) );

	// set up the thermometer
	thermo.setFillBrush( QBrush(Qt::red) );
	thermo.setRange(0, 20);
	thermo.show();


	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData[index] = 0;
	}

	// make a plot curve from the data and attach it to the plot
	curve.setSamples(xData, yData, plotDataSize);
	curve.attach(&plot);

	plot.replot();
	plot.show();


	// set up the layout - knob above thermometer
	vLayout.addWidget(&knob);
	vLayout.addWidget(&thermo);

	// plot to the left of knob and thermometer
	hLayout.addLayout(&vLayout);
	hLayout.addWidget(&plot);

	setLayout(&hLayout);

	// Initilise ADC
	adc_init();

	// Initialise LED display
	led_init(800, 2400);
}


void Window::timerEvent( QTimerEvent * )
{
	double inVal;
	unsigned short adc_in;
	++count;

	// Get value from ADC
	adc_in= adc_read();
	printf("ADC: %d\n", adc_in);
	inVal = adc_in*gain;

	// add the new input to the plot
	memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
	yData[plotDataSize-1] = inVal;
	curve.setSamples(xData, yData, plotDataSize);
	plot.replot();

	// Output to the LED Thermometer
	led_write(adc_in);

	// set the on-screen thermometer value
	thermo.setValue( inVal + 10 );
}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}

