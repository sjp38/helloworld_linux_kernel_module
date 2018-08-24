obj-m := cputime.o

cputime.ko:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: cputime.ko
	sudo insmod $^
	
unload: cputime.ko
	sudo rmmod $^
