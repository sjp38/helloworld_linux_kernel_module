mname=list_example

obj-m := $(mname).o

$(mname).ko: $(mname).c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: $(mname).ko
	sudo insmod $^
	
unload: $(mname).ko
	sudo rmmod $^
