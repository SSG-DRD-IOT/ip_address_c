#
# Copyright (c) 2017 Intel Corporation.
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

all:	ip_addr_c

ip_addr_c:	ip_addr.c
	gcc ip_addr.c -o ip_addr_c -I/usr/include/upm -lupmc-utilities -lmraa -lm -lupm-jhd1313m1 -lupmc-jhd1313m1 -lupm-lcm1602 -lupmc-lcm1602 -lpcap

up2:	ip_addr_c_up2

ip_addr_c_up2:	ip_addr.c
	gcc -DUP2_MRAA_SUBPLATFORM ip_addr.c -o ip_addr_c_up2 -I/usr/include/upm -lupmc-utilities -lmraa -lm -lupm-jhd1313m1 -lupmc-jhd1313m1 -lupm-lcm1602 -lupmc-lcm1602 -lpcap

clean:
	rm -rf ip_addr_c
	rm -rf ip_addr_c_up2
	rm -rf *.o
