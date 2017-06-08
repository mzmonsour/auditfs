KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build

obj-m += auditfs.o

auditfs-objs := super.o

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(KMOD_DIR) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(KMOD_DIR) clean
