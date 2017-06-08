RM ?= rm -f
MV := mv
CC := gcc
MKDIR := mkdir

OUT_DIR ?= $(PWD)/bin
KMOD_DIR := $(PWD)/src/kmod
KMOD := auditfs.ko
export KMOD_DIR

.PHONY: all module clean

all: module

module: $(OUT_DIR)
	$(MAKE) -C $(KMOD_DIR)
	$(MV) $(KMOD_DIR)/$(KMOD) $(OUT_DIR)/

clean:
	$(MAKE) -C $(KMOD_DIR) clean
	$(RM) $(OUT_DIR)/*

$(OUT_DIR):
	$(MKDIR) -p $(OUT_DIR)
