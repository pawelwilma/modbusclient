#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <pwilma@wp.pl> wrote this file.  As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return.               Pawel
# ----------------------------------------------------------------------------
include $(TOPDIR)/rules.mk

PKG_NAME:=modbusclient
PKG_RELEASE:=1
PKG_LICENSE:=Beerware

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
    TARGET_CFLAGS += -D_DEFAULT_SOURCE
endif

define Build/Compile
	$(TARGET_CC) -Wall -o $(PKG_BUILD_DIR)/modbusclient modbusclient.c  $(TARGET_LIBS)
endef

define Package/modbusclient/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/modbusclient $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,modbusclient))
