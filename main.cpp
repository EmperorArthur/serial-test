//USB Serial Test application
//Copyright Arthur Moore 2013
//GPL V3
//Use this with an RS232 tester to make sure that the serial port you're using supports all the lines.
//Cheap chinese USB to RS232 adapters dont!!!

#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>			//For cout/cin
#include <stdio.h>			//For getchar
#include <errno.h>			//For errno
#include <string>			//For strings

using namespace std;

string stringError(int errornumber){
	if(EBADF == errornumber)
		return "not a valid descriptor";
	if(EFAULT == errornumber)
		return "references an inaccessible memory area";
	if(EINVAL == errornumber)
		return "Request or argp is not valid";
	if(ENOTTY == errornumber)
		return "not associated with a character special device";
}

int main(int argc, char * argv[]){
	int fd;				//The file descriptor for the serial device
	string serialName = "/dev/ttyUSB0";	//The file name of the serial device
	//If there's an option given to the command, it's the name of the serial device
	if(2 == argc){
		serialName = argv[1];
	}
	
	// open the serial device
	cout << "Opening " << serialName << endl;
	fd = open(serialName.c_str(), O_RDWR || O_NONBLOCK);

	// adjust serial communuication parameters
	struct termios ComParams;
	tcgetattr(fd, &ComParams);
	ComParams.c_cflag &= ~CBAUD; // baud rate = 9600 bd
	ComParams.c_cflag |= B9600;
	tcsetattr( fd, TCSANOW, &ComParams );

	// play with RTS & DTR
	int iFlags;

	// turn on RTS
	iFlags = TIOCM_RTS;
	if( -1 == ioctl(fd, TIOCMBIS, &iFlags) ){
		cout << "Error turning on RTS: " << stringError(errno) <<endl;
	}
	
	// turn on DTR
	iFlags = TIOCM_DTR;
	if( -1 == ioctl(fd, TIOCMBIS, &iFlags) ){
		cout << "Error turning on DTR: " << stringError(errno) <<endl;
	}

	// turn on CTS
	iFlags = TIOCM_CTS;
	if( -1 == ioctl(fd, TIOCMBIS, &iFlags) ){
		cout << "Error turning on CTS: " << stringError(errno) <<endl;
	}

	// turn on CD
	iFlags = TIOCM_CD;
	if( -1 == ioctl(fd, TIOCMBIS, &iFlags) ){
		cout << "Error turning on CD: " << stringError(errno) <<endl;
	}
	
	// turn on DSR
	iFlags = TIOCM_DSR;
	if( -1 == ioctl(fd, TIOCMBIS, &iFlags) ){
		cout << "Error turning on DSR: " << stringError(errno) <<endl;
	}
	
	//Waiting for char
	getchar();

	// turn off RTS
	iFlags = TIOCM_RTS;
	if( -1 == ioctl(fd, TIOCMBIC, &iFlags) ){
		cout << "Error turning off RTS: " << stringError(errno) <<endl;
	}

	// turn off DTR
	iFlags = TIOCM_DTR;
	if( -1 == ioctl(fd, TIOCMBIC, &iFlags) ){
		cout << "Error turning off DTR: " << stringError(errno) <<endl;
	}

	// turn off CTS
	iFlags = TIOCM_CTS;
	if( -1 == ioctl(fd, TIOCMBIC, &iFlags) ){
		cout << "Error turning off CTS: " << stringError(errno) <<endl;
	}
	
	// turn off CD
	iFlags = TIOCM_CD;
	if( -1 == ioctl(fd, TIOCMBIC, &iFlags) ){
		cout << "Error turning off CD: " << stringError(errno) <<endl;
	}
	
	// turn off DSR
	iFlags = TIOCM_DSR;
	if( -1 == ioctl(fd, TIOCMBIC, &iFlags) ){
		cout << "Error turning off DSR: " << stringError(errno) <<endl;
	}

	//Waiting for char
	getchar();

	return 0;
}
