obj-m += char_driver.o
obj-m += step2.o
obj-m += step3.o
obj-m += step4.o
obj-m += step5_.o

KSRC=/home/user/workspace/kernelws/KSRC
all:
	make -C ${KSRC} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
clean:
	make -C ${KSRC} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
