#pragma once

//#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "tlvcdp.h"
#include "tlvlldp.h"
#include "dissectors.h"

const char* appType = "SERVER";

typedef unsigned char BYTE;

struct TLV
{
	int type;
	int length;
	char* value;
};

struct IndexValue
{
	int index;
	char* value;
};

IndexValue lldp_tlv_type[] =
{
	{ LLDP_END, "End of LLDPDU" },
	{ LLDP_CHASSIS_ID, "Chassis ID" },
	{ LLDP_PORT_ID, "Port ID" },
	{ LLDP_TTL, "Time To Live" },
	{ LLDP_PORT_DESC, "Port Description" },
	{ LLDP_SYSTEM_NAME, "System Name" },
	{ LLDP_SYSTEM_DESC, "System Description" },
	{ LLDP_SYSTEM_CAP, "System Capabilities" },
	{ LLDP_MGMT_ADDR, "Management Address" },
	{ LLDP_ORG_SPEC, "Organisation-specific LLDP" },
};

IndexValue cdp_tlv_type[] =
{
	{ 0x01, "Device-ID" },
	{ 0x02, "Address" },
	{ 0x03, "Port-ID" },
	{ 0x04, "Capability" },
	{ 0x05, "Version String" },
	{ 0x06, "Platform" },
	{ 0x07, "Prefixes" },
	{ 0x08, "Protocol-Hello Option" },
	{ 0x09, "VTP Management Domain" },
	{ 0x0a, "Native VLAN ID" },
	{ 0x0b, "Duplex" },
	{ 0x0e, "ATA-186 VoIP VLAN request" },
	{ 0x0f, "ATA-186 VoIP VLAN assignment" },
	{ 0x10, "Power Consumption" },
	{ 0x11, "MTU" },
	{ 0x12, "AVVID trust bitmap" },
	{ 0x13, "AVVID untrusted ports CoS" },
	{ 0x14, "System Name" },
	{ 0x15, "System Object ID (not decoded)" },
	{ 0x16, "Management Addresses" },
	{ 0x17, "Physical Location" },
	{ 0, NULL }
};

#ifdef WIN32
typedef unsigned char   u_char;
//#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")
#endif
#ifdef __linux__
#include <sys/socket.h>
#endif

// include this BEFORE pcap.h
// This will then use remote-ext.h
// https://www.winpcap.org/pipermail/winpcap-users/2008-June/002576.html
#define HAVE_REMOTE

//WinPcap libraries. This can be done in the project C++/Linker properties
#include "pcap.h"
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

// To read

/*

//std map

//sockets
http://www.cplusplus.com/forum/beginner/139578/
https://msdn.microsoft.com/en-us/library/windows/desktop/bb530747%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396

//Hex double digits
http://stackoverflow.com/questions/11070183/sprintf-how-to-print-hexadecimal-number-with-leading-0-to-have-width-2

//Ascii values
http://web.cs.mun.ca/~michael/c/ascii-table.html
http://www.asciitable.com/

//CDP spec
http://docstore.mik.ua/univercd/cc/td/doc/product/lan/trsrb2/frames.pdf
http://linux-ha.org/source-doc/assimilation/html/group__cdp__type__fields.html
https://searchcode.com/codesearch/view/14642040/
https://github.com/boundary/wireshark/blob/master/epan/dissectors/packet-cdp.c
http://cgit.osmocom.org/wireshark/plain/epan/dissectors/packet-cdp.c
http://www.cs.technion.ac.il/Courses/Computer-Networks-Lab/projects/spring2003/cdp2/web_cdp2/web_cdp2/cdp2_report.htm

//CURL
http://curl.haxx.se/libcurl/c/example.html
http://curl.haxx.se/libcurl/c/simple.html
http://curl.haxx.se/libcurl/c/http-post.html
http://stackoverflow.com/questions/20171165/getting-libcurl-to-work-with-visual-studio-2013

http://wxwidgets.info/cross-platform-way-of-obtaining-mac-address-of-your-machine/
http://www.codeguru.com/cpp/i-n/network/networkinformation/article.php/c5451/Three-ways-to-get-your-MAC-address.htm

*/

// To go

/*

//#include <ntddndis.h> //fir gettubg tge nac address

//CURL library
//Need this to be static, ideally
#define CURL_STATICLIB
#include "curl/curl.h"
#pragma comment ( lib, "libcurl.lib" )

//#define _USE_IP_AND_MASK 
//For now just use the first octet to determine if its the network address. 
//It will be probably anyway. But itd make it more flexible to be able to specify a network address
#ifdef _USE_IP_AND_MASK
#define CORPORATE_ADDRESS	"10.1.0.0";
#define CORPORATE_MASK		"255.255.255.0";
#endif

// Receiving and Displaying an answer from the Web Server
//char buffer[10000];
//ZeroMemory(buffer, sizeof(buffer));
//int dataLen;
//while ((dataLen = recv(webSocket, buffer, sizeof(buffer), 0) > 0))
//{
//	int i = 0;
//	while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
//		printf("%c", buffer[i]);
//		i += 1;
//	}
//}


/* 
		//the CURL way
			CURL * curl;

			curl_global_init(CURL_GLOBAL_ALL); //Do we need this?
			CURLcode res;
			curl = curl_easy_init();

			if (curl)
			{
			curl_easy_setopt(curl, CURLOPT_URL, address);

			//POST versus get
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
			//http://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c


			res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			}

			curl_easy_cleanup(curl);
			}

			curl_global_cleanup();
*/