obj-m := hellod.o​

# TODO: check if our tx2 dir matches the example 
kernel_DIR := /usr/src/linux-headers-4.9.201-tegra-ubuntu18.04_aarch64/kernel-4.9/​

PWD := $(shell pwd)​

all:
	make -C $(kernel_DIR) SUBDIRS=$(PWD)​

clean:
	rm *.o *.ko *.mod.c​

install:
	insmod hello.ko 
	dmesg 

uninstall:
	rmmod hello.ko
	dmesg
	
lsmod:
	lsmod | grep hellod

.PHONY: clean​