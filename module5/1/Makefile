obj-m += hello.o

all:
	CONFIG_MODULE_SIG=n
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	CONFIG_MODULE_SIG=n
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean