APP = bof
APP_SRCS += shellcode.c

APP_CFLAGS += -fno-stack-protector 
APP_CFLAGS += -O0 -g
APP_CFLAGS += -z execstack
APP_CFLAGS += -DSTATS
include $(RULES_DIR)/pmsis_rules.mk
