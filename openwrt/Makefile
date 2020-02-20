#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=modbusclient
PKG_RELEASE:=1
PKG_LICENSE:=GPL-2.0+

include $(INCLUDE_DIR)/package.mk

define Package/modbusclient
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=OpenWRT Modbus client
  MAINTAINER:=Pawel Wilma (pwilma@wp.pl)
  DEPENDS:=+libmodbus
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LIBS += -lmodbus

ifneq ($(CONFIG_USE_GLIBC),)
    TARGET_CFLAGS += -D_DEFAULT_SOURCE -lmodbus
endif

define Build/Compile
	$(TARGET_CC) -Wall -o $(PKG_BUILD_DIR)/modbusclient modbusclient.c  $(TARGET_LIBS)
endef

define Package/modbusclient/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/modbusclient $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,modbusclient))
