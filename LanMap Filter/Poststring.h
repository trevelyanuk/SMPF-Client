#pragma once

//Sizes for each of the strings
#define SZ_HOST 64
#define SZ_IP 64
#define SZ_SWPORT 64
#define SZ_VLAN 16
#define SZ_MAC 17
#define SZ_SWIP 17
#define SZ_SWNAME 17
#define SZ_SWMAC 17

class Poststring
{
public: 
	static char postdata[512];

	static char systemip[32];
	static int slsystemip;
	static char* prefixip;
	static char* ip;

	static char systemhostname[32];
	static int slsystemhostname;
	static char* prefixhost;
	static char* host;

	static char systemvlan[32];
	static int slsystemvlan;
	static char* prefixvlan;
	static char* vlan;

	static char systemswitchport[32];
	static int slsystemswitchport;
	static char* prefixswPort;
	static char* swPort;

	static char systemswName[32];
	static int slsystemswName;
	static char* prefixswName;
	static char* swName;

	static char systemmac[18];
	static int slsystemmac;
	static char* prefixmac;
	static char* mac;

	static char systemswIP[64];
	static int slsystemswIP;
	static char* prefixswIP;
	static char* swIP;

	static char systemswMAC[32];
	static int slsystemswMAC;
	static char* prefixswMAC;
	static char* swMAC;

	static char systemsourceproto[5];
	static int slsystemsourceproto;
	static char* prefixsourceproto;
	static char* sourceproto;

	static char* url;

	static void GeneratePOSTData() {};
	static void addStrings(char** result, const char* prefix, const char* body, int& prefixlength, int& bodylength) {};
	static char* GeneratePOSTString(char* settingsServer, char* settingsPage) {};
};

