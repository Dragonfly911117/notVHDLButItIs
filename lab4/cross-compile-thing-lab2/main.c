#include "util.h"
#include"Pins.h"


void LED_ON(unsigned int pin) {
	gpio_export(pin);
	gpio_set_dir(pin, "out");
	gpio_set_value(pin, "1");
}

void LED_OFF(unsigned int pin) {
	gpio_set_value(pin, "0");
	gpio_unexport(pin);
}

int main(int argc, char **argv) {
	int input;
	int PIN;
	int i;

        /*
LEDs:
    12
    18
    19
    23
*/
        
	switch (argv[1][3]) {
		case '0':
			PIN = PIN_19;
			break;
		case '1':
			PIN = PIN_18;
			break;
		case '2':
			PIN = PIN_19;
			break;
		case '3':
			PIN = PIN_23;
			break;
	}

	if (argv[2][1] == 'n') {
		LED_ON(PIN);
	} else if (argv[2][1] == 'f') {
		LED_OFF(PIN);
	}
	

	
	for (i = 0; i < 5; ++i) {
		LED_ON(PIN_12);
		LED_ON(PIN_18);
		sleep(1);
		LED_OFF(PIN_12);
		LED_OFF(PIN_18);

		LED_ON(PIN_19);
		LED_ON(PIN_23);
		sleep(1);
		LED_OFF(PIN_19);
		LED_OFF(PIN_23);
	}
	

	return 0;
}
