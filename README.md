Volumeter
===========

Volumeter is an application for measuring volume levels.

Making it work
--------------

To clone the git repository:

    git clone https://github.com/jpentland/qwt-example

To build:

    cd qwt-example
    qmake
    make

Enable I2C driver:

Edit the file /etc/modprobe.d/raspi-blacklist.conf, and comment out the line:

blacklist i2c-bcm2708

Then run:

sudo modprobe i2c-dev

To run (assuming you are logged into the RPi over ssh and no X-server is running):

		
		Connect the Volumeter hardware to the Raspberry Pi, and run:

    sudo startx ./volumeter

		To log data to a file, use:

		sudo startx ./volumeter filename
