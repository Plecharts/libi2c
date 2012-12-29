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

all: libi2c

libi2c:
	make -C $(SRCDIR) all
	mkdir -p $(BINDIR)
	$(CC) -shared -Wl,-soname,libi2c.so.0 -o $(BINDIR)/libi2c.so.0.1 src/i2c.o
	

clean:
	rm -rf *.so.*
	rm -rf $(BINDIR)
	make -C $(SRCDIR) clean