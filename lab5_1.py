# sudo pip install Jetson.GPIO

# Python gpio setting
from re import T
import Jetson.GPIO as GPIO
import time

'''Make sure gpio below...'''
## SPI gpio:
CLK = 23                                                    ######## 已確認 Pin 19 - SPI(3) MOSI Pin 21 - SPI(3) MISO Pin 23 - SPI(3) CLK Pin 24 - SPI(3) CS#0
MISO = 21
MOSI = 19
CS = 24
output_pin = 7
## MCP3008 gpio:
photo_ch = 0

## PORT init
def init():
    GPIO.setmode(GPIO.BOARD)                                #指定一個編號系統
    GPIO.setup(output_pin, GPIO.OUT, inital = GPIO.HIGH)    #腳位需要作為I/O
    GPIO.setwarnings(False)
    GPIO.cleanup()                                          #清除正在使用的腳位編號系統
    GPIO.setmode(GPIO.BCM)
    # SPI interface pins
    GPIO.setup(MOSI, GPIO.OUT)
    GPIO.setup(MISO, GPIO.IN)
    GPIO.setup(CLK, GPIO.OUT)
    GPIO.setup(CS, GPIO.OUT)


# Read SPI data from MCP3088 (感測器)
def readsens(sensnum, clkpin, mosipin, misopin, cspin):
    if ((sensnum > 7) | (sensnum < 0)):
        return -1
    GPIO.output(cspin, True)                                #start CS high
    GPIO.output(clkpin, False)                              #start clk low
    GPIO.output(cspin, False)                               #bring CS low
    
    ## GPIO　-> ADC (Analog to Digital Converter) ; ADC read Analog Digital
    commandOut = sensnum
    commandOut |= 0x18                                      #start bit + single-ended bit
    commandOut <<= 3                                        
    for i in range(5):                                      #send 5 bits
        if (commandOut & (0x18)):
            GPIO.output (mosipin, True)
        else:
            GPIO.output (mosipin, False)
        commandOut <<= 1
        GPIO.output(clkpin, True)
        GPIO.outupt(clkpin, False)
    
    ## ADC -> GPIO ADC output Digital... 
    sensout = 0
    for  i in range(12):                                    ## read in one empty bit, one null bit and 10 ADC bits ; 1+1+10 = 12
        GPIO.output(clkpin, True)
        GPIO.output(clkpin, False)
        sensout <<= 1
        if (GPIO.input(misopin)):
            sensout |= 0x1
    GPIO.output(cspin, True)
    sensout >>= 1                                           ## 1' bit is null; so drop it!

    return sensout

def main():
    init()
    while True:
        sens_value = readsens(photo_ch, CLK, MOSI, MISO, CS)
        print(sens_value)                                   ## result2: 終端機上顯示當前光敏電阻數值
        time.sleep(1)
if __name__ == '__main__':
    try:
        main()
    except Exception:
        pass
