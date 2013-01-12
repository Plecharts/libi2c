#
# Copyright (c) 2012 - 2013 Jaroslav Peska
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

all: libi2c.o

libi2c.o: libi2c.c libi2c.h
	$(CC) -c -fPIC $(CCFLAGS) libi2c.c -o libi2c.o

clean:
	rm -rf libi2c.o

.PHONY: clean