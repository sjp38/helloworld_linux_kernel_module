kdir=/lib/modules/$(shell uname -r)/build

module_name=misc_dev_example
obj-m := $(module_name).o

$(module_name).ko: $(module_name).c
	make -C $(kdir) M=$(PWD) modules

clean:
	make -C $(kdir) M=$(PWD) clean

load: $(module_name).ko
	sudo insmod $^

unload: $(module_name).ko
	sudo rmmod $^
