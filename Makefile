#
# Copyright (c) 2012 Jaroslav Peska
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc.
# 51 Franklin Street, Fifth Floor
# Boston, MA  02110-1301
# USA

CC = gcc
CCFLAGS = -Wall -O3
LINKFLAGS =
SRCDIR = src
BINDIR = bin
LIBI2C_VERSION_MAJOR = 0
LIBI2C_VERSION_MINOR = 1
LIBI2C_VERSION_PATCH = 0


all: libi2c

libi2c:
	make -C $(SRCDIR) all
	mkdir -p $(BINDIR)

	$(CC) src/i2c.o -shared $(CCFLAGS) $(LINKFLAGS) \
	-Wl,-soname,libi2c.so.$(LIBI2C_VERSION_MAJOR) \
	-o $(BINDIR)/libi2c.so.$(LIBI2C_VERSION_MAJOR).$(LIBI2C_VERSION_MINOR).$(LIBI2C_VERSION_PATCH)

	cp $(SRCDIR)/i2c.h $(BINDIR)/libi2c.h

install: all
	install -m 644 $(BINDIR)/libi2c.so.0.1.0 /usr/lib
	install -m 644 $(BINDIR)/libi2c.h /usr/include

clean:
	rm -rf *.so.*
	rm -rf $(BINDIR)
	make -C $(SRCDIR) clean

.PHONY: install clean