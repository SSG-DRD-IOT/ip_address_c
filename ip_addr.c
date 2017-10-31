/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <pcap.h>

#include "jhd1313m1.h"
#include "upm.h"
#include "upm_utilities.h"
#include "signal.h"
#include "string.h"


bool shouldRun = true;

char str1[1];

void sig_handler(int signo)
{
    if (signo == SIGINT)
        shouldRun = false;
}

int main()
{
    signal(SIGINT, sig_handler);

    struct ifaddrs *ifaddr, *ifa;
    struct sockaddr_in *sa;
    char *addr;
    char *device;
    char errbuf[PCAP_ERRBUF_SIZE];

    device = pcap_lookupdev(errbuf);

    if (getifaddrs(&ifaddr) == -1) 
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
    {
        if (ifa->ifa_addr == NULL)
            continue;  

        if(ifa->ifa_addr->sa_family==AF_INET)
        {
	  
          if(strcmp(ifa->ifa_name,device)==0) {

	    sa = (struct sockaddr_in *) ifa->ifa_addr;
	    addr = inet_ntoa(sa->sin_addr);
	    printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);

	    };
        }
    }
    
    freeifaddrs(ifaddr);
    
    // initialize a JHD1313m1 on I2C bus 0, LCD address 0x3e, RGB
    // address 0x62
    jhd1313m1_context lcd = jhd1313m1_init(512, 0x3e, 0x62);

    if (!lcd)
    {
        printf("jhd1313m1_i2c_init() failed\n");
        return 1;
    }

    char str2[20];
    uint8_t rgb[7][3] = {
        {0xd1, 0x00, 0x00},
        {0xff, 0x66, 0x22},
        {0xff, 0xda, 0x21},
        {0x33, 0xdd, 0x00},
        {0x11, 0x33, 0xcc},
        {0x22, 0x00, 0x66},
        {0x33, 0x00, 0x44}};


    while (shouldRun)
    {
      
      snprintf(str2, sizeof(str2), "%s", addr);

      jhd1313m1_set_cursor(lcd, 0, 2);
  
      jhd1313m1_write(lcd, str2, strlen(str2));

      // Change the color
      uint8_t r = rgb[255][0];
      uint8_t g = rgb[142][0];
      uint8_t b = rgb[58][0];
       
      jhd1313m1_set_color(lcd, r, g, b);

      upm_delay(1);
      
    };

    return 0;
}
