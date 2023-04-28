import Jetson.GPIO as GPIO
import time

SPICLK = 11
SPIMISO = 9
SPIMOSI = 10
SPICS = 8

output_pin = 26
output_pin2 = 18
photo_ch = 0


def init():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    GPIO.cleanup()
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(SPIMOSI, GPIO.OUT)
    GPIO.setup(SPIMISO, GPIO.IN)
    GPIO.setup(SPICLK, GPIO.OUT)
    GPIO.setup(SPICS, GPIO.OUT)
    GPIO.setup(output_pin, GPIO.OUT)
    GPIO.setup(output_pin2, GPIO.OUT)

def readadc(adcnum, clockpin, mosipin, misopin, cspin):
    if (adcnum > 7) or (adcnum < 0):
        return -1
    GPIO.output(cspin, True)

    GPIO.output(clockpin, False)
    GPIO.output(cspin, False)

    commandout = adcnum
    commandout |= 0x18
    commandout <<= 3
    for i in range(5):
        if commandout & 0x80:
            GPIO.output(mosipin, True)
        else:
            GPIO.output(mosipin, False)
        commandout <<= 1
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)
    adcout = 0
    for i in range(12):
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)
        adcout <<= 1
        if GPIO.input(misopin):
            adcout |= 0x1
    GPIO.output(cspin, True)
    adcout >>= 1
    return adcout


def main():
    init()
    while True:
        adc_value = readadc(photo_ch, SPICLK, SPIMOSI, SPIMISO, SPICS)
        print(adc_value)
        if (adc_value > 900):
            GPIO.output(output_pin,True)
            GPIO.output(output_pin2,True)
            print("LED on")
            print("LED2 on")
        elif (900 > adc_value > 200):
            GPIO.output(output_pin,False)
            GPIO.output(output_pin2,True)
            print("LED off")
            print("LED2 on")
	else:
        GPIO.output(output_pin,False)
        GPIO.output(output_pin2,False)	
        print("LED off")
        print("LED2 off")	
        time.sleep(1)



if __name__ == '__main__':
    main()

