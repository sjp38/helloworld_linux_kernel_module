obj-m := kthread.o

kthread.ko:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: kthread.ko
	sudo insmod $^
	
unload: kthread.ko
	sudo rmmod $^
