#obj-m += char_driver.o
#obj-m += step2.o
#obj-m += step3.o
#obj-m += step4.o
#obj-m += step5.o
#obj-m += listdemo.o
#obj-m += race.o
#obj-m += conc.o
#obj-m += kthread.o
#obj-m += ioctl.o
#obj-m += race1.o
#obj-m += race1fix.o
#obj-m += race2.o
obj-m  += listapi.o 
KSRC=/home/user/workspace/kernelws/KSRC
all:
	make -C ${KSRC} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
clean:
	make -C ${KSRC} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
