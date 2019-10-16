#scripts/kconfig/Makefile

# File name: Makefile (PMSD_IMdriver/)
# Code author: Ramana R (github@Rr42)
# Code version: v1.0.1
# Application: PMSD Interface Module driver
# Description: 
# 	This code ficitilates easy compilation, testing and deploynment for the PMSD Interface Module driver.
# License:
#   Copyright (C) 2019  Ramana R (github@Rr42)
#   
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

obj-m     += PMSDIMDriverMod.o
PMSDIMDriverMod-y := PMSDIMDriver.o gpioCore.o PMSDErrorCodes.o

KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

MAJOR_NUM := $(shell cat /proc/devices | grep PMSDIMD | grep -oEi "([0-9]+)")

SUBDIRS := $(wildcard */)

TOPTARGETS := all clean

all: PMSDIMD Uapps

PMSDIMD: PMSDIMDriverMod.ko

Uapps: $(SUBDIRS)

$(TOPTARGETS): $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

PMSDIMDriverMod.ko:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

load:
	@sh PMSDIMDriverRun.sh 1 0 
	@sleep 2

install: load
	$(eval MAJOR_NUM := $(shell cat /proc/devices | grep PMSDIMD | grep -oEi "([0-9]+)") )

	@mknod /dev/PMSDIMDriver c $(shell cat /proc/devices | grep PMSDIMD | grep -oEi "([0-9]+)") 0
	@echo Device file created

	@chmod 777 /dev/PMSDIMDriver
	@echo Device file permission granted

uninstall:
	@sh PMSDIMDriverRun.sh 2 0
	@rm /dev/PMSDIMDriver
	@echo Device file removed

clean:
	rm -rf *.o *.ko *.mod *.symvers *.order .*.cmd *.mod.c .tmp_versions .cache.mk

.PHONY: $(TOPTARGETS) $(SUBDIRS)
