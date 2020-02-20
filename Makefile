# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <pwilma@wp.pl> wrote this file.  As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return.               Pawel
# ----------------------------------------------------------------------------

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LIBS += -lmodbus

modbusclient: modbusclient.c
	$(CC) -o modbusclient modbusclient.c  -lmodbus



