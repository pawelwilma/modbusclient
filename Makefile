TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LIBS += -lmodbus

#$(CC) -Wall -o $(PKG_BUILD_DIR)/modbusclient $(PKG_BUILD_DIR)/modbusclient.c
modbusclient: modbusclient.c
	$(CC) -o modbusclient modbusclient.c  -lmodbus



