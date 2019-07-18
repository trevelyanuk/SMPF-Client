#include "stdafx.h"
int TestMACaddress(BYTE *addr);
void LogfileOutput(char * text);

int SetCurrentAdapter(int network);
int FindAdapterForNetwork(int octet);
int InitCapture();
void StartCapture();
void GeneratePOSTData();
void GeneratePOSTString();
int UploadData(char * address, char * data);


void printInterface(pcap_if_t *d);
//char * testTargetNetwork(pcap_if_t * adapter);
//bool doesnt exist in C
bool testTargetNetwork(pcap_if_t * adapter);
void * get_in_addr(struct sockaddr *sa);
char * ipToString(u_long in);
int checkErrors();
int getCorrectNetwork();
void getListOfAdapters();
int hackyNetworkAddress(char* test);

//C does not use pass by reference, only value. Pointers are values so we should use pointers if we want to do this in C
void addStrings(char ** result, const char * prefix, const char * body, int &prefixlength, int &bodylength);
//char * addstrings(char * result, char * prefix, char * body, int &prefixlength, int &bodylength);
void getDataLLDP();
void getDataCDP();
int LoadConfig();

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

int _tmain(int argc, _TCHAR* argv[])
{
	LoadConfig();
	GetAdapterList();
	FindAdapterForNetwork(settingsNetwork);

	GetSwitchData();
	GetHostData();

	GeneratePOSTString();

	if (appType == "SERVER")
	{
		UploadData(settingsServer, postdata);
	}

	WSACleanup();

	LogfileOutput("");
	return 0;
}

int FindAdapterForNetwork(int firstOctet)
{
	int selectedAdapterIndex = 0;
	int temp1;

	//originally was allAdapters->next - but this has to be the current adapter otherwise it will only ever check the first two!!!
	for (adapter = allAdapters; adapter; adapter = adapter->next)
	{
		++temp1;
		if (AdapterHasOctet(adapter, settingsNetwork))
		{
			printf("\nComputer is currently attached to the %d network through adapter %d", settingsNetwork, temp1);
			printf("\n");

			selectedAdapterIndex = temp1;
		}
	}
	//Is anything beyond here actually needed?
	if (selectedAdapterIndex == -1)
	{
		LogfileOutput("No Ethernet adapters found that match the target network", 2);
		return -1;
	}

	adapter = allAdapters;

	//selectedAdapterNumber - 1 is necessary because i 0 will actually be adapter 1
	for (int i = 0; i < selectedAdapterIndex - 1; i++)
	{
		adapter = adapter->next;
	}
	return 0;
}

void GetSwitchData()
{
	InitCapture();
	StartCapture();
}

void GetHostData()
{
	
}

int GetAdapterList()
{
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allAdapters, errorBuffer) == -1)
	{
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

//0 info, 1 warning, 2 error
void LogfileOutput(char * message, int errorLevel)
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

void *get_in_addr(struct sockaddr *socket_address)
{
	if (socket_address->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)socket_address)->sin_addr);
	}
	return &(((struct sockaddr_in6*)socket_address)->sin6_addr);
}

//This is what we use to compare the interfaces against our network identity.
bool AdapterHasOctet(pcap_if_t * adapter, int firstOctet)
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

	int temp1, temp2, temp3, temp4;

	if (selectedAdapterIPaddress[2] == '.')
	{
		temp1 = (selectedAdapterIPaddress[0] - '0') * 10;
		temp2 = (selectedAdapterIPaddress[1] - '0') * 1;
		temp3 = 0;
	}
	else
	{
		temp1 = (selectedAdapterIPaddress[0] - '0') * 100;
		temp2 = (selectedAdapterIPaddress[1] - '0') * 10;
		temp3 = (selectedAdapterIPaddress[2] - '0') * 1;
	}

	return (temp1 + temp2 + temp3 == firstOctet);
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
void PrintListOfAdapters()
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

int UploadData(char * address, char * data)
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
		return -1;
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
		return -1;
	}

	// Establishing a connection to the web Socket
	printf("\nConnecting... ");
	if (connect(webSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0)
	{
		LogfileOutput("Could not connect");
		closesocket(webSocket);
		return -1;
	}
	printf("Connected");

	// Sending a HTTP-GET-Request to the Web Server
	const char* httpRequest = data;
	int sentBytes = send(webSocket, httpRequest, strlen(httpRequest), 0);
	if (sentBytes < strlen(httpRequest) || sentBytes == SOCKET_ERROR)
	{
		LogfileOutput("Could not send the request to the server");
		closesocket(webSocket);
		return -1;
	}

	return 0;
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

int InitCapture()
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

void StartCapture()
{
//	LogfileOutput(sprintf("\n Capture session started for adapter (%s)\n", adapter->name));
	//Free the list created by findalldevs because we don't need it anymore.
	pcap_freealldevs(allAdapters);	

	time_t start;
	time_t now;
	time(&start);
	time(&now);

	int retValue;

	while ((retValue = pcap_next_ex(captureInstance, &packetHeader, &packetData)) >= 0)
	{
		time(&now);
		if ((now - start) > settingsTimeout)
		{
			LogfileOutput("Exiting: timeout has exceeded. Either increase the timeout or check to see that you are broadcasting the packets that you are checking for.");
			return;
		}

		if (retValue == 0)
		{
			printf("\rWaiting for packets.. %i", (int) (now - start));
			continue;
		}

		int packetLength = packetHeader->len;
		int testPacketType = (packetData[12] << 8 | packetData[13]);

		printf("\n%d:%d:%d length of packet: %d\n\n", (packetHeader->ts.tv_sec % 86400) / 3600, (packetHeader->ts.tv_sec % 3600) / 60, packetHeader->ts.tv_sec % 60, packetLength);

		switch (testPacketType)
		{
			case LLDP: {
				if (settingsLLDP)
				{
					if (Dissectors::GetDataLLDP(packetData, packetLength) != 0)
					{
						continue;
					}
					sprintf_s(systemsourceproto, "LLDP");
					slsystemsourceproto = strlen(systemsourceproto);
				}
				break;
			}
			default: {
				if (settingsLLDP)
				{
					if (Dissectors::GetDataCDP(packetData, packetLength) !=0 )
					{
						continue;
					}
					sprintf_s(systemsourceproto, "CDP");
					slsystemsourceproto = strlen(systemsourceproto);
				}

			}
		}

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
	int slhost = strlen(prefixhost);
	int slip = strlen(prefixip);
	int slvlan = strlen(prefixvlan);
	int slmac = strlen(prefixmac);
	int slswPort = strlen(prefixswPort);
	int slswName = strlen(prefixswName);
	int slswIP = strlen(prefixswIP);
	int slswMAC = strlen(prefixswMAC);
	int slsourceproto = strlen(prefixsourceproto);

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

void GeneratePOSTString()
{

	GeneratePOSTData();
	sprintf_s(postdata,
		"POST %s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
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