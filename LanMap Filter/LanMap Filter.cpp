#include "stdafx.h"

typedef unsigned char BYTE;

int TestMACaddress(BYTE *addr);
void LogfileOutput(char * text);

void GetHostNameWindows();
void GetHostNameLinux();
void GetHostNameApple();
void GetHostName();
void GetMACaddressWindows();
void GetMACaddressLinux();
void GetMACaddressApple();
void GetMACaddress();

int setCurrentAdapter();
int initCapture();
void capture();
void generatePOSTData();
void generatePOSTString();
void uploadString(char * address, char * data);
int saveHost();

void printInterface(pcap_if_t *d);
//char * testTargetNetwork(pcap_if_t * adapter);
//bool doesnt exist in C
bool testTargetNetwork(pcap_if_t * adapter);
void * get_in_addr(struct sockaddr *sa);
string ipToString(u_long in);
int checkErrors();
int getCorrectNetwork();
void getListOfAdapters();
int hackyNetworkAddress(char* test);

//C does not use pass by reference, only value. Pointers are values so we should use pointers if we want to do this in C
void addStrings(char ** result, const char * prefix, const char * body, int &prefixlength, int &bodylength);
//char * addstrings(char * result, char * prefix, char * body, int &prefixlength, int &bodylength);
void getDataLLDP();
void getDataCDP();
int loadConfig();

const char* appType = "SERVER";

pcap_if_t			*	allAdapters;		//Used to store all the adapters in a list (by storing references to next adapters)
pcap_if_t			*	adapter;			//Used to store one of the adapters in a list.
pcap_t				*	captureInstance;	//Used to store a capture
struct pcap_pkthdr	*	packetHeader;		//Packet header
const u_char		*	packetData;			//Packet data


char * server;
char postdata[512]; 

char systemip[32] = "";
int slsystemip;
char * prefixip;
char * ip;

char systemhostname[32] = "";
int slsystemhostname;
char * prefixhost;
char * host;

char systemvlan[32] = "";
int slsystemvlan;
char * prefixvlan;
char * vlan;

char systemswitchport[32] = "";
int slsystemswitchport;
char * prefixswPort;
char * swPort;

char systemswName[32] = "";
int slsystemswName;
char * prefixswName;
char * swName;

char systemmac[18] = "";
int slsystemmac;
char * prefixmac;
char * mac;

char systemswIP[64] = "";
int slsystemswIP;
char * prefixswIP;
char * swIP;

char systemswMAC[32] = "";
int slsystemswMAC;
char * prefixswMAC;
char * swMAC;

char systemsourceproto[5] = "";
int slsystemsourceproto;
char * prefixsourceproto;
char * sourceproto;

char * url;

//Sizes for each of the strings
#define SZ_HOST 64
#define SZ_IP 64
#define SZ_SWPORT 64
#define SZ_VLAN 16
#define SZ_MAC 17
#define SZ_SWIP 17
#define SZ_SWNAME 17
#define SZ_SWMAC 17

//Error buffer, used to store error message
//Size of buffer is decided by PCAP_ERRBUF_SIZE..
//..which is 256 at the time of writing
char errorBuffer[PCAP_ERRBUF_SIZE];
char * settingsServer;
char * settingsPage;
int settingsNetwork;
int settingsTimeout;
int settingsCDP;
int settingsLLDP;

struct TLV
{
	int type;
	int length;
	char* value;
};

struct IndexValue
{

//This holds just a value and a character (*string)
//Then we make an array of them, called tlv_type
	int index;
	char * value;
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

int _tmain(int argc, _TCHAR* argv[])
{
	loadConfig();
	
	if (setCurrentAdapter() > 0)
	{
		initCapture();
		capture();
		GetHostName();
		GetMACaddress();
		generatePOSTData();
		generatePOSTString();
		saveHost();
		if (appType == "SERVER")
		{
			uploadString(settingsServer, postdata);
		}

		WSACleanup();
	}

	LogfileOutput("");
	return 0;
}

void LogfileOutput(char * text)
{

	//If we are running this in debug, then we display it on the screen
#ifdef _DEBUG
	printf("\n");
	printf(text);

	//Pauses the system so that it will only close on user input
	system("PAUSE");
#endif

	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char * timeywimey = asctime(timeinfo);
	timeywimey[strlen(timeywimey) - 1] = 0;
	
	//Needs to be made into a relative path or something!
	char * fileName = "C:/ProgramData/switchyMcLogFile.txt"; 

	FILE *pFile;
	errno_t errorCode = fopen_s(&pFile, fileName, "a");
	if (!pFile)
	{
	}
	else
	{
		fputs("\n", pFile);
		fputs(timeywimey, pFile);
		fputs(": ", pFile);
		fputs(text, pFile);

		fclose(pFile);
	}
}

int getCorrectNetwork()
{
	int temp1 = 0;

	//originally was allAdapters->next - but this has to be the current adapter otherwise it will only ever check the first two!!!
	for (adapter = allAdapters; adapter; adapter = adapter->next)

	{
		++temp1;
		if (testTargetNetwork(adapter))
		{
			printf("\nComputer is currently attached to the %d network through adapter %d", settingsNetwork, temp1);
			printf("\n");

			return temp1;
		}
	}
	//Fail
	return -1;
}

//I hate that this has the same name as the WinSock gethostname and that its only case sensitivity that separates them!
void GetHostName()
{
#ifdef _WIN32
	GetHostNameWindows();
#endif 
#ifdef __linux__
	GetHostNameLinux();
#endif 
#ifdef __APPLE__
	GetHostNameApple();
#endif
}
void GetHostNameApple()
{
	gethostname(systemhostname, 64);
	slsystemhostname = strlen(systemhostname);
}
void GetHostNameLinux()
{
	gethostname(systemhostname, 64);
	slsystemhostname = strlen(systemhostname);
}
//explain this under "other useful stuff"
void GetHostNameWindows()
{
	WSADATA wsaData; //Or WSAData wsaData;

					 //MAKEWORD does what I do later and makes one 16 bit value from 2 8 bit values (one is bitshifted)
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		LogfileOutput("WSAStartup failed.");
		exit(1);
	}

	//Might have to use uname?
	//Use a temporary variable to get the system hostname and store the length
	gethostname(systemhostname, 64);
	slsystemhostname = strlen(systemhostname);
	//int x = WSAGetLastError();

}

void GetMACaddress()
{
#ifdef _WIN32
	GetMACaddressWindows();
#endif 
#ifdef __linux__
	GetMACaddressLinux();
#endif 
#ifdef __APPLE__
	GetMACaddressApple();
#endif

}
void GetMACaddressApple()//pcap_if_t * addapter_correct)
{
}
void GetMACaddressLinux()//pcap_if_t * addapter_correct)
{
}
void GetMACaddressWindows()//pcap_if_t * addapter_correct)
{	
	IP_ADAPTER_INFO AdapterInfo[16];       // Allocate information for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo(      // Get list of adapters on system
		AdapterInfo,                 // [out] buffer to receive data
		&dwBufLen);                  // [in] size of receive data buffer
									 //assert(dwStatus == ERROR_SUCCESS);  // Verify return value is valid, no buffer overflow

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // Contains pointer to
												 // current adapter info

	do 
	{
		//Heres that dodgy way of finding the address again..
		//int temp1, temp2, temp3, temp4;
		if (hackyNetworkAddress(pAdapterInfo->IpAddressList.IpAddress.String) == settingsNetwork)
		{
			TestMACaddress(pAdapterInfo->Address);
		}
		pAdapterInfo = pAdapterInfo->Next;    // Progress through linked list
	} 
	while (pAdapterInfo);                    // Terminate if last adapter
}


int TestMACaddress(BYTE *addr)
{
	//%02x means hex (the x) and print in the format of having 2 characters. prefixes with a 0 if theres nothing
	printf("\nMac Address: %02x:%02x:%02x:%02x:%02x:%02x", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);


	_snprintf_s(systemmac, SZ_MAC, "%02x:%02x:%02x:%02x:%02x:%02x", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
	slsystemmac = strlen(systemmac);


	//This test is to rule out virtual mac addreses based on the first two octets. Can add more cases later.
	if (addr[0] == 0x00)
	{
		if (addr[1] == 0x50) //or 80?
		{			
			return 1;
		}
	}
	return 0;
}

int checkErrors()
{
	//This is a really bad error, hence -1 is returned if it fails
	//Stores all the adapters into the allAdapters variable
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allAdapters, errorBuffer) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs_ex function: %s\n", errorBuffer);
		LogfileOutput("Error in pcap_findalldevs_ex function");
		return -1;
	}

	//This is also an error, but it isn't bad because we might just have no adapters.
	if (allAdapters == NULL)
	{
		LogfileOutput("No Adapters found! Make sure WinPcap is installed.");
		return 1;
	}

	return 0;
}

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

//This is what we use to compare the interfaces against our network identity.
bool testTargetNetwork(pcap_if_t * adapter)
{
	IP_ADAPTER_INFO AdapterInfo[16];       // Allocate information for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo(      // Get list of adapters on system
		AdapterInfo,                 // [out] buffer to receive data
		&dwBufLen);                  // [in] size of receive data buffer
									 //assert(dwStatus == ERROR_SUCCESS);  // Verify return value is valid, no buffer overflow

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // Contains pointer to
												 // current adapter info


	//Store the IP in this char array called test
	char selectedAdapterIPaddress[INET6_ADDRSTRLEN];

	//Store the IP address(es) of the adapter in this pointer
	pcap_addr_t * adapterAddress;

	for (adapterAddress = adapter->addresses; adapterAddress; adapterAddress = adapterAddress->next)
	{

		if (adapterAddress->addr->sa_family == AF_INET)
		{
			// ipToString(((struct sockaddr_in *)adapterAddress->addr)->sin_addr.s_addr)); ???
			inet_ntop(adapterAddress->addr->sa_family,
				get_in_addr((struct sockaddr *)adapterAddress->addr),
				selectedAdapterIPaddress,
				sizeof(selectedAdapterIPaddress));
		}
	}
	do
	{
		if (*(pAdapterInfo->IpAddressList.IpAddress.String) == *selectedAdapterIPaddress)
		{
			if ((pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET) && (WINVER > _WIN32_WINNT_WS03))
			{
			}
			else
			{
				//LogfileOutput("Either the version of Windows is too low or the selected adapter is wireless");
				return false;
			}
		}	
		pAdapterInfo = pAdapterInfo->Next;    // Progress through linked list
	} 
	while (pAdapterInfo);

	//strlen makes sure we stop at \0
	//Copy this over so we can use it as the string to submit later
	slsystemip = strlen(selectedAdapterIPaddress);
	memcpy(systemip, selectedAdapterIPaddress, slsystemip);
	//slsystemip = strlen(systemip);

	//REALLY dodgy way to do this. Implies that the first three digits will always be an IP address.
	//First we check to see if the third character is a decimal point
	//This is because the IP address will just be stored as it is first read, so "10." will occupy the same space as "192"
	//Need to check if AF_INET first
	//And we should probably try and check the entire address!
	//Need to find out how to convert all these chars to an int, preferably full-stop delimited!

	

	//http://www.programmingforums.org/post14042.html
	//http://stackoverflow.com/questions/4463676/sockaddr-print-all-information-which-sa-data-holds-c
	//http://stackoverflow.com/questions/2774766/can-you-explain-how-this-ip-to-string-function-works


	return (hackyNetworkAddress(selectedAdapterIPaddress) == settingsNetwork);
}

int hackyNetworkAddress(char* test)
{
	int temp1, temp2, temp3, temp4;

	if (test[2] == '.')
	{
		temp1 = (test[0] - '0') * 10;
		temp2 = (test[1] - '0') * 1;
		temp3 = 0;
	}
	else
	{
		temp1 = (test[0] - '0') * 100;
		temp2 = (test[1] - '0') * 10;
		temp3 = (test[2] - '0') * 1;
	}

	temp4 = temp1 + temp2 + temp3;

	//What is the difference between the print types?
	//printf("%d\n", temp4);
	//printf("%d\n", CORPORATE_ADDRESS);

	return temp4;
}

// Prints information about an interface. 
// Takes an interface, so we can do this for all of our interfaces in a loop
void printInterface(pcap_if_t * adapter)
{
	//This will be extracted from an interface we give this function
	pcap_addr_t * adapterAddress;

	//An array of 128 chars is used to hold an ipV6 string. Why?! IPv6 is only 64. I don't get this.
	char ip6str[128];

	//Name
	//Description
	//Is this a loopback address?
	//IP address(es)
	printf("%s\n", adapter->name);
	printf("\tDescription: %s\n", adapter->description);
	printf("\tLoopback: %s\n", (adapter->flags & PCAP_IF_LOOPBACK) ? "yes" : "no");

	//Set the interfaceAddress to be a pointed to the list of addresses on a given device.
	//So long as the address exists (IE it is not Null, this is a different way of doing the above, I like it more)
	//Then we will set it to be the next one
	//And print info
	for (adapterAddress = adapter->addresses; adapterAddress; adapterAddress = adapterAddress->next)
	{
		printf("\tAddress Family: #%d\n", adapterAddress->addr->sa_family);

		switch (adapterAddress->addr->sa_family)
		{
		case AF_INET:
			printf("\tAddress Family Name: AF_INET\n");
			
			if (adapterAddress->addr)
				printf("\tAddress: %s\n", ipToString(((struct sockaddr_in *)adapterAddress->addr)->sin_addr.s_addr));
			if (adapterAddress->netmask)
				printf("\tNetmask: %s\n", ipToString(((struct sockaddr_in *)adapterAddress->netmask)->sin_addr.s_addr));
			if (adapterAddress->broadaddr)
				printf("\tBroadcast Address: %s\n", ipToString(((struct sockaddr_in *)adapterAddress->broadaddr)->sin_addr.s_addr));
			if (adapterAddress->dstaddr)
				printf("\tDestination Address: %s\n", ipToString(((struct sockaddr_in *)adapterAddress->dstaddr)->sin_addr.s_addr));
			break;

		case AF_INET6:
			//We could ignore this for now, nobody gives a shit about ipv6 anyway
			printf("\tAddress Family Name: AF_INET6\n");
			if (adapterAddress->addr)
				printf("\tAddress: %s\n", ip6ToString(adapterAddress->addr, ip6str, sizeof(ip6str)));
			break;

		default:
			LogfileOutput("Address Family Name: Unknown");
			break;
		}
	}
	printf("\n");
}

/* From tcptraceroute, convert a numeric IP address to a string */
#define IPTOSBUFFERS    12
char * ipToString(u_long in)
{
	static char output[3 * 4 + 3 + 1];
	u_char *p;

	p = (u_char *)&in;
	
	_snprintf_s(output, sizeof(output), sizeof(output), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return output;
}

bool compareNetworks(u_char * ipAddress, u_char * subnetMask)
{
	return 0;
}

//Iterate through allAdapters and print the name and description.
//If adapter is NULL, that is the end of the adapter list.
//adapter !=NULL is the same as adapter on its own
void getListOfAdapters()
{

	//Where else is this even used
	int totalAdapters = 0;
	for (adapter = allAdapters; adapter; adapter = adapter->next)
	{
		printf("\n%d) ", ++totalAdapters);// , adapter->name);
		printf("-- %s\n", adapter->description);
		printInterface(adapter);
	}
	//Just add a blank line. Makes it look pretty.
	printf("\n");
}


void addStrings(char ** result, const char * prefix, const char * body, int &prefixlength, int &bodylength)
{
	*result = (char *)malloc((prefixlength + bodylength + 1) * sizeof(char));
	memcpy(*result, prefix, prefixlength);
	memcpy(*result + prefixlength, body, bodylength);
	(*result)[prefixlength + bodylength] = '\0'; //Must be set like this as array notation takes precendence over a dereferencing
	prefixlength = strlen(*result);
}

void uploadString(char * address, char * data)
{
	// We first prepare some "hints" for the "getaddrinfo" function
	// to tell it that we are looking for an IPv4 connection.
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;          // We are targeting IPv4
	hints.ai_protocol = IPPROTO_TCP;    // We are targeting TCP
	hints.ai_socktype = SOCK_STREAM;    // We are targeting TCP so its SOCK_STREAM

										// Aquiring of the IPv4 address of a host using the newer
										// "getaddrinfo" function which outdated "gethostbyname".
										// It will search for IPv4 addresses using the TCP-Protocol.
	struct addrinfo* targetAdressInfo = NULL;
	DWORD getAddrRes = getaddrinfo(address, NULL, &hints, &targetAdressInfo);

	if (getAddrRes != 0 || targetAdressInfo == NULL)
	{
		LogfileOutput("Could not resolve the hostname.");
	}

	// Create the Socket Address Informations, using IPv4
	// We dont have to take care of sin_zero, it is only used to extend the length of SOCKADDR_IN to the size of SOCKADDR
	SOCKADDR_IN sockAddr;
	sockAddr.sin_addr = ((struct sockaddr_in*) targetAdressInfo->ai_addr)->sin_addr;    // The IPv4 Address from the Address Resolution Result
	sockAddr.sin_family = AF_INET;  // IPv4
	sockAddr.sin_port = htons(80);  // HTTP Port: 80

									// We have to free the Address-Information from getaddrinfo again
	freeaddrinfo(targetAdressInfo);

	// Creation of a socket for the communication with the Web Server,
	// using IPv4 and the TCP-Protocol
	SOCKET webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (webSocket == INVALID_SOCKET)
	{
		LogfileOutput("Creation of the socket failed!");
	}

	// Establishing a connection to the web Socket
	printf("\nConnecting... ");
	if (connect(webSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0)
	{
		LogfileOutput("Could not connect");
		closesocket(webSocket);
	}
	printf("Connected");

	// Sending a HTTP-GET-Request to the Web Server
	const char* httpRequest = data;
	int sentBytes = send(webSocket, httpRequest, strlen(httpRequest), 0);
	if (sentBytes < strlen(httpRequest) || sentBytes == SOCKET_ERROR)
	{
		LogfileOutput("Could not send the request to the server");
		closesocket(webSocket);
	}
}

void printPacketData(const u_char * data, int length, char * format)
{
	int rows = 0;
	int rowcounter = 0;
	for (int x = 0; x < length; x++)
	{
		rowcounter++;
		if (rowcounter == 8)
		{
			printf(" ");
		}
		if (rowcounter == 16)
		{
			printf("\n");
			rowcounter = 0;
			rows++;
		}
		printf(format, data[x]);
	}
}
int setCurrentAdapter()
{
	int selectedAdapterNumber = 0;

	if (checkErrors() != 0)
	{
		//Ok we need to modify this. How do I put this on one line so it returns checkErrors only if it isnt 0?
		return -1;
	}

	//getListOfAdapters();


	if ((selectedAdapterNumber = getCorrectNetwork()) == -1)
	{
		LogfileOutput("No Ethernet adapters found that match the target network");
		printf("\nNo adapters found that match the current network starting with %i", settingsNetwork);
		return -1;
	}



	// Select an adapter on the system. 
	//Used for debug - in production, we will select adapter based on the active connection.
	//printf("Please enter a number between 1 and %d: ", currentAdapter);
	//scanf_s("%d", &selectedAdapterNumber);	

	/*if (selectedAdapterNumber < 1 || selectedAdapterNumber > totalAdapters)
	{
	printf("\nAdapter number out of range.\n");
	pcap_freealldevs(allAdapters);
	system("PAUSE");
	return -1;
	}*/


	// Reset the currently selected adapter to be allAdapers again
	adapter = allAdapters;

	//selectedAdapterNumber - 1 is necessary because i 0 will actually be adapter 1
	for (int i = 0; i < selectedAdapterNumber - 1; i++)
	{
		adapter = adapter->next;
	}
	return 0;

}

int initCapture()
{

	/**/
	/**/
	//Opens a new packet capture on the selected adapter, identified by its name
	//Pakcet length of 65536 means it will capture an entire packet
	//Promiscuous mode means it will capture all traffic.
	//Usually only data intended for that host will be captured.
	//1000 is the timeout in MS. May reduce this later.. or increase. Could be up to
	//30 seconds to get an LLDP/CDP packet.
	//Authentication on the remote machine isnt needed.. whats this about?
	//Reference to the error buffer to use.
	captureInstance = pcap_open(adapter->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 600, NULL, errorBuffer);

	if (captureInstance == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter %s\n", adapter->name);
		pcap_freealldevs(allAdapters);
		//Pauses the system so that it will only close on user input
#ifdef _DEBUG
		system("pause");
#endif
		return -1;
	}


	//LLDP
	//http://wiki.wireshark.org/LinkLayerDiscoveryProtocol

	//CDP
	//http://wiki.wireshark.org/CDP
	//http://www.rhyshaden.com/cdp.htm

	//Ethernet II frames have their ethertype in bytes 12 and 13
	//Ethernet (802.3) with SNAP has their vendor code in 20 and 21 in the SNAP header

	//winpcap only recognises "ether proto" to look at bytes 12 and 13 so we have to look at 20 and 21 too
	//So it wont even look there

	//From wireshark: 
	//"LLC/SNAP: CDP is encapsulated as LLC/SNAP with an OUI of 0x00000C and a protocol ID of 0x2000."
	//"Ethernet: Typically, LLDP uses Ethernet as its "transport" protocol. The Ethernet type for LLDP is 0x88cc."

	//The following checks the 12/13th packet of an ethernet frame and the 20th and 21st. 
	//EthernetII and Ethernet/SNAP packets have their ethertype defined in each of the respective locations
	//The first is LLDP, second is CDP.

	char packet_filter[45] = "";

	if (settingsCDP && settingsLLDP)
	{
		sprintf_s(packet_filter, "ether[12:2] = 0x88cc or ether[20:2] = 0x2000");
	}
	else
		if (settingsCDP)
		{
			sprintf_s(packet_filter, "ether[20:2] = 0x2000");

		}
		else
			if (settingsLLDP)
			{
				sprintf_s(packet_filter, "ether[12:2] = 0x88cc");

			}
			else
			{
				sprintf_s(packet_filter, ";");

				LogfileOutput("Oh dear, we didn't set any value for CDP or LLDP! This program will not be filtering any data; nothing will be receieved..");
			}


	//http://www.kuliniewicz.org/discovery/html/img3.html


	//Now to add filters so we only get those two
	//Maybe try these links in future. 
	//Interstingly, Windump has no implementation of print-lldp!
	//http://www.opensource.apple.com/source/tcpdump/tcpdump-32/tcpdump/print-lldp.c
	//http://www.opensource.apple.com/source/tcpdump/tcpdump-32/tcpdump/print-cdp.c


	//Set the filter to be that which we specified above
	struct bpf_program fcode;
	pcap_compile(captureInstance, &fcode, packet_filter, 1, ((struct sockaddr_in *)(adapter->addresses->netmask))->sin_addr.S_un.S_addr);
	pcap_setfilter(captureInstance, &fcode);

	return 0;
}

void OutputText(const char *) {

}
void capture()
{
	OutputText("\n Capture session started for adapter (%s)\n", adapter->name);
	//Free the list created by findalldevs because we don't need it anymore.
	pcap_freealldevs(allAdapters);	

	time_t start;
	time_t now;
	time(&start);
	time(&now);

	int retValue;
	//pcap_next_ex does something. It stores packet header data, the data itself and 
	//a reference to the capture stream.
	while ((retValue = pcap_next_ex(captureInstance, &packetHeader, &packetData)) >= 0)
	{
		time(&now);
		if ((now - start) > settingsTimeout)
		{
			LogfileOutput("Exiting: timeout has exceeded. Either increase the timeout or check to see that you are broadcasting the packets that you are checking for.");
			exit(0);
		}

		//triggered on timeout
		if (retValue == 0)
		{
			printf("\rWaiting for packets.. %i", (int) (now - start));

			continue;
		}
		//printf("length of packet: %d\n", packetHeader->len);


		printf("\n%d:%d:%d length of packet: %d\n", (packetHeader->ts.tv_sec % 86400) / 3600, (packetHeader->ts.tv_sec % 3600) / 60, packetHeader->ts.tv_sec % 60, packetHeader->len);



		//http://www.tcpdump.org/pcap.htm
		//http://ubuntuforums.org/showthread.php?t=1015748&page=2&s=6f5f0d325f5eb49d8b7daacecc812d34

		//pointers are a fixed size (an address of memory)
		//the type matters so you can increment by one unit of whatever youre using
		//So with our u_char pointer we can move forward by some characters in the array

		//But why does it display lots of characters and not just one
		//And how can a const char hold so many characters?

		//Problem is also that it reads a 00 (\0) as a null-termination character!

		printf("\n");




		//We can assume if we get this far, we definitely have either an LLDP or a CDP packet
		//
		//So these two bytes in packetData represent the ethertype in an ethernet frame.
		//"OR"ing these two means that it will give you a 1 if either of them have a 1 at that bit in memory.
		//This is the best way to actually put data in somewhere, but we dont want to really add them up
		//So we shift the first lot of data 8 places to the left. 
		//This means that we get a huge number but, interpreted at hex, that is actually the decimal number we want
		int testPacketType = (packetData[12] << 8 | packetData[13]);

	

		//http://stackoverflow.com/questions/1816451/are-there-any-curl-alternatives-for-c
		//http://yuba.stanford.edu/~casado/pcap/section2.html
		//https://www.google.co.uk/webhp?sourceid=chrome-instant&rlz=1C1WSCB_enGB561GB561&ion=1&espv=2&ie=UTF-8#q=the%20assimilation%20project


		//		Now to find the host's mac address. It seems it isn't really that easy; I had hoped that Winpcap had some function for this but apparently not.There seem to be a few ways to do it, the easiest is to use GetAdapterAddresses(plural is important - most of the PCs I will be using this on have multiple network adapters)






		//http://www.wildpackets.com/resources/compendium/ethernet/frame_snap_iee8023
		//http://www.informit.com/library/content.aspx?b=CCNP_Studies_Troubleshooting&seqNum=53

		//The thing is, because CDP doesnt actually have their ethertype in the same place due to being different ethernet types,
		//then we can assume that if test is not 0x88cc, then (packetData[20] << 8 | packetData[21]) has to be 0x2000.
		//VLAN probably doesnt need the bitshift as you can't get a VLAN ID that big.
		if (testPacketType == LLDP)
		{
			if (settingsLLDP)
			{
				getDataLLDP();
				sprintf_s(systemsourceproto, "LLDP");
				slsystemsourceproto = strlen(systemsourceproto);
			}
		}

		else
		{
			getDataCDP();
			sprintf_s(systemsourceproto, "CDP");
			slsystemsourceproto = strlen(systemsourceproto);
		}





		/* TLV Reader */

		//char packetData[1000] = "";
		//memcpy(&packetData,packetData , packetHeader->len);
		//
		//for (int x = 0; x < packetHeader->len; x++)
		//{
		//		printf("%c", packetData[x]);
		//}

		//char packetData[1000] = "";
		//memcpy(&packetData, packetData, packetHeader->len);

		//for (int x = 0; x < packetHeader->len; x++)
		//{
		//	if ((packetData[x] == ASCII_SHIFT_OUT) || (packetData[x] == '\0'))
		//	{
		//		printf("%c", "\n");
		//	}
		//	else
		//	{
		//		printf("%c", packetData[x]);
		//	}
		//}



		//if (packetData[count] < 32)
		//{

		//	if ((packetData[count]) == '\n' || (packetData[count] == '\0'))
		//	{
		//		printf("\n");
		//	}
		//	else
		//	{
		//		printf(" *%i* ", packetData[count]);
		//	}
		//}
		//else
		//{

		//	if (packetData[count] > 122)
		//	{
		//		printf(" *%i* ", packetData[count]);
		//	}

		//	else {
		//		printf("%c", packetData[count]);
		//	}
		//}

		//unsigned becausae we dont want values to be negative
		//unsigned char packetData[1000] = "";
		//memcpy(&packetData, packetData, packetHeader->len);

		// nl (\n) = 0x0a = 10
		// nul (\0) = 0x00 = 0


		//Error with packet. Get the error from the current capture instance
		if (retValue == -1)
		{
			printf("Error reading packet: %s\n", pcap_geterr(captureInstance));
		}
		else
		{
			break;
		}

	}
}
void generatePOSTData()
{

	//Each of these is instantiated as a new character array, essentially, with the first element as the pointer
	//server = settingsServer;
	prefixhost = "host=";
	prefixip = "ip=";
	prefixmac = "mac=";
	prefixvlan = "vlan=";

	prefixswPort = "swPort=";
	prefixswName = "swName=";
	prefixswIP = "swIP=";
	prefixswMAC = "swMAC=";
	prefixsourceproto = "sp=";

	//Now we get the size of each of these arrays
	//int slserver = strlen(server);
	int slhost = strlen(prefixhost);
	int slip = strlen(prefixip);
	int slvlan = strlen(prefixvlan);
	int slmac = strlen(prefixmac);

	int slswPort = strlen(prefixswPort);
	int slswName = strlen(prefixswName);
	int slswIP = strlen(prefixswIP);
	int slswMAC = strlen(prefixswMAC);
	int slsourceproto = strlen(prefixsourceproto);


	//host = addstrings(host, prefixhost, systemhostname, slhost, slsystemhostname);
	addStrings(&host, prefixhost, systemhostname, slhost, slsystemhostname);
	addStrings(&ip, prefixip, systemip, slip, slsystemip);
	addStrings(&vlan, prefixvlan, systemvlan, slvlan, slsystemvlan);
	addStrings(&mac, prefixmac, systemmac, slmac, slsystemmac);

	addStrings(&swPort, prefixswPort, systemswitchport, slswPort, slsystemswitchport);
	addStrings(&swIP, prefixswIP, systemswIP, slswIP, slsystemswIP);
	addStrings(&swName, prefixswName, systemswName, slswName, slsystemswName);
	addStrings(&swMAC, prefixswMAC, systemswMAC, slswMAC, slsystemswMAC);

	addStrings(&sourceproto, prefixsourceproto, systemsourceproto, slsourceproto, slsystemsourceproto);





	//We make a new blank set of memory that will hold it all
	//This is the size of all the above multiplied by the size of what a character is
	//Actually character is just one byte, and malloc uses bytes as its storage unit size
	//But if we were doing ints or objects, we would have to put the type in
	//Note that ( 10 * sizeof(int)) is the same as (sizeof someArrayOfTenInts)
	//Oh and we make some extra space so we can add & symbols
	//Look at sPrint later
	//Do I need a terminating last 1 char?
	//http://stackoverflow.com/questions/1383649/concatenating-strings-in-c-which-method-is-more-efficient


	//url = (char *)malloc((slserver + slhost + slip + slswport + slvlan + 3 + 1) * sizeof(char)); //GET
	url = (char *)malloc((slhost + slip + slswPort + slvlan + slmac + slswName + slswIP + slswMAC + slsourceproto + 8 + 1) * sizeof(char));


	memcpy(url,
		host, slhost);
	url[slhost] = '&';


	memcpy(url + slhost + 1,
		ip, slip);
	url[slhost + slip + 1] = '&';


	memcpy(url + slhost + slip + 2,
		swPort, slswPort);
	url[slhost + slip + slswPort + 2] = '&';


	memcpy(url + slhost + slip + slswPort + 3,
		vlan, slvlan);
	url[slhost + slip + slswPort + slvlan + 3] = '&';


	memcpy(url + slhost + slip + slswPort + slvlan + 4,
		mac, slmac);
	url[slhost + slip + slswPort + slvlan + slmac + 4] = '&';




	memcpy(url + slhost + slip + slswPort + slvlan + slmac + 5,
		swName, slswName);
	url[slhost + slip + slswPort + slvlan + slmac + slswName + 5] = '&';


	memcpy(url + slhost + slip + slswPort + slvlan + slmac + slswName + 6,
		swIP, slswIP);
	url[slhost + slip + slswPort + slvlan + slmac + slswName + slswIP + 6] = '&';


	memcpy(url + slhost + slip + slswPort + slvlan + slmac + slswName + slswIP + 7,
		swMAC, slswMAC);
	url[slhost + slip + slswPort + slvlan + slmac + slswName + slswIP + slswMAC + 7] = '&';


	memcpy(url + slhost + slip + slswPort + slvlan + slmac + slswName + slswIP + slswMAC + 8,
		sourceproto, slsourceproto);
	url[slhost + slip + slswPort + slvlan + slmac + slswName + slswIP + slswMAC + slsourceproto + 8] = '\0';



	//	memcpy(postdata, url, 256);

}

//Separated out the server and page elements in the config file. Removed http:// as a prefix for the server address
//Removed cURL libraries and directory references and moved to native sockets due to simplicity and not needing extra external libraries.

void generatePOSTString()
{
	sprintf_s(postdata,
		"POST %s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"// this wont work! text/html
		"Content-Length: %i\r\n\r\n"
		"%s\r\n", settingsPage, settingsServer, strlen(url), url);
}

int saveHost()
{
	if (appType == "SIMPLE")
	{
		char * fileName = "PC_list.txt";
		FILE *pFile;
		errno_t errorCode = fopen_s(&pFile, fileName, "a");
		if (!pFile)
		{
			//		fprintf(stderr, "opening %s: %s\n", argv[1], strerror(errno));
			//	system("PAUSE");
			return 1;
		}

		fputs(systemhostname, pFile);
		fputs(" is connected to port ", pFile);
		fputs(systemswitchport, pFile);
		fputs(" on switch ", pFile);
		fputs(systemswName, pFile);
		fputs(" (", pFile);
		fputs(systemswIP, pFile);
		fputs(")\n", pFile);
		fclose(pFile);

	}

	if (appType == "CSV")
	{
		char * fileName = "hosts.csv";
		FILE *pFile;
		errno_t newFileOrNot = fopen_s(&pFile, fileName, "r");
		if (newFileOrNot == 0)
		{
			fclose(pFile);
		}

		errno_t errorCode = fopen_s(&pFile, fileName, "a");
		if (!pFile)
		{
			//		fprintf(stderr, "opening %s: %s\n", argv[1], strerror(errno));
			//	system("PAUSE");
			return 1;
		}

		if (newFileOrNot == 2)
		{
			fputs("\"Hostname\",\"Host IP\",\"Switchport\",\"VLAN\",\"MAC Address\",\"Switch name\",\"Switch IP\",\"Switch MAC\"\n", pFile);

		}

		fputs("\"", pFile);
		fputs(systemhostname, pFile);
		fputs("\",\"", pFile);
		fputs(systemip, pFile);
		fputs("\",\"", pFile);
		fputs(systemswitchport, pFile);
		fputs("\",\"", pFile);
		fputs(systemvlan, pFile);
		fputs("\",\"", pFile);
		fputs(systemmac, pFile);
		fputs("\",\"", pFile);
		fputs(systemswName, pFile);
		fputs("\",\"", pFile);
		fputs(systemswIP, pFile);
		fputs("\",\"", pFile);
		fputs(systemswMAC, pFile);
		fputs("\"", pFile);
		fputs("\n", pFile);
		fclose(pFile);
	}
	return 0;
}

#define TEXTSIZE 64

int loadConfig()
{

	char * fileName = "config.ini";
	//FILE *pFile = fopen_s(fileName, "r");
	FILE *pFile;
	errno_t errorCode = fopen_s(&pFile, fileName, "r");
	char buffer2[TEXTSIZE][TEXTSIZE];

	//Strips out all of these (space, equals, comma, new line, semi colon)
	char * delimiters = " =,\n;";

	if (!pFile)
	{
		//		fprintf(stderr, "opening %s: %s\n", argv[1], strerror(errno));
		//	system("PAUSE");
		return 1;
	}

	size_t linesRead = 0;

	while (fgets(buffer2[linesRead], TEXTSIZE, pFile) != NULL)
	{
		//comments and new lines are missed

		//Skips lines beginning with # or that are blank
		if (buffer2[linesRead][0] == '\n' || buffer2[linesRead][0] == '#')
		{
			//break this iteration of the while loop if it isn't a valid string
			continue;
		}


		char * next;
		char * variable;
		//strtok will return a pointer to a string of characters which are separated by whatever we tell it to separate
		//by, such as an =. It will return the address at the point of the first string of chars.
		variable = strtok_s(buffer2[linesRead], delimiters, &next);

		//Probably a blank, skip this one
		if (!variable)
		{
			continue;
		}

		if (strcmp(variable, "server") == 0)
		{
			variable = strtok_s(NULL, delimiters, &next);
			if (!variable)
			{
				LogfileOutput("Error in configuration file: no value for server address!");
				return 2;
			}

			settingsServer = (char *)malloc((strlen(variable) + 1) * sizeof(char));
			memcpy(settingsServer, variable, strlen(variable));
			settingsServer[strlen(variable)] = '\0';
			printf("\nServer address is %s", variable);
		}
		else if (strcmp(variable, "page") == 0)
		{
			variable = strtok_s(NULL, delimiters, &next);
			if (!variable)
			{
				LogfileOutput("Error in configuration file: no value for page!");
				return 2;
			}

			settingsPage = (char *)malloc((strlen(variable) + 1) * sizeof(char));
			memcpy(settingsPage, variable, strlen(variable));
			settingsPage[strlen(variable)] = '\0';
			printf("\nPage is %s", variable);
		}
		else if (strcmp(variable, "network") == 0)
		{
			variable = strtok_s(NULL, delimiters, &next);
			if (!variable)
			{
				LogfileOutput("Error in configuration file: no value for network!");
				return 2;
			}
			settingsNetwork = atoi(variable);
			printf("\nNetwork is %s", variable);
		}
		else if (strcmp(variable, "timeout") == 0)
		{
			variable = strtok_s(NULL, delimiters, &next);
			if (!variable)
			{
				LogfileOutput("Error in configuration file: no value for timeout!");
				return 2;
			}
			settingsTimeout = atoi(variable);
			printf("\nTimeout is %s", variable);
		}
		else if (strcmp(variable, "protocdp") == 0)
		{

			//null means that it will carry on scanning from where the previous strtok ended
			//Means we can carry on with the same line
			variable = strtok_s(NULL, delimiters, &next);
			if (!variable)
			{
				LogfileOutput("Error in configuration file: no value for protocdp!");
				return 2;
			}
			if (strcmp(variable, "true") == 0)
			{
				settingsCDP = 1;
			}
			else
			{
				settingsCDP = 0;
			}

			printf("\nCDP is %s", variable);
		}
		else if (strcmp(variable, "protolldp") == 0)
		{
			variable = strtok_s(NULL, delimiters, &next);
			if (!variable)
			{
				LogfileOutput("Error in configuration file: no value for protolldp!");
				return 2;
			}
			if (strcmp(variable, "true") == 0)
			{
				settingsLLDP = 1;
			}
			else
			{
				settingsLLDP = 0;
			}
			printf("\nLLDP is %s", variable);
		}
		else if (strcmp(variable, "local") == 0)
		{
			variable = strtok_s(NULL, delimiters, &next);
			if (!variable)
			{
				LogfileOutput("Error in configuration file: no value for locally stored captures!");
				return 2;
			}
			if (strcmp(variable, "CSV") == 0)
			{
				appType = "CSV";
			}
			else if(strcmp(variable, "SIMPLE") == 0)
			{
				appType = "SIMPLE";
			}

			printf("\nLocal capture of data is stored as type: %s", variable);
		}
		else
		{
			continue;
		}

		//http://www.linuxquestions.org/questions/programming-9/read-parameters-from-config-file-file-parser-362188/

		linesRead++;
	}

	fclose(pFile);
	return 0;
}