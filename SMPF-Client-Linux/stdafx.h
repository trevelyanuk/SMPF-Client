// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"

#include <stdio.h>

//#include <tchar.h>

#include "tlvcdp.h"
#include "tlvlldp.h"

#ifdef WIN32
//#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")
#endif
#ifdef __linux__
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#endif

// include this BEFORE pcap.h
// This will then use remote-ext.h
// https://www.winpcap.org/pipermail/winpcap-users/2008-June/002576.html
#define HAVE_REMOTE

//WinPcap libraries. This can be done in the project C++/Linker properties
#include <pcap/pcap.h>
#ifdef WIN32
	#pragma comment (lib, "wpcap.lib")
#endif
#pragma comment (lib, "Packet.lib")

// Get mac address! The hacky way..
#ifdef WIN32
	#include <Iphlpapi.h>
	#pragma comment (lib,"Iphlpapi.lib")
	#pragma comment (lib,"Rpcrt4.lib")
#endif

//#define COMPILE_AS_C
#ifdef COMPILE_AS_C
#include <stdbool.h>
//typedef int bool;
//#define true 1
//#define false 0
#endif