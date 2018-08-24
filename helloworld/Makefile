obj-m := hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: hello.ko
	sudo insmod hello.ko
	
unload: hello.ko
	sudo rmmod hello.ko
