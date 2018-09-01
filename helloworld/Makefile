obj-m := hello.o

hello.ko: hello.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: hello.ko
	sudo insmod $^
	
unload: hello.ko
	sudo rmmod $^
