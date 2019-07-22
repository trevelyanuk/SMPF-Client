#pragma once
#include "stdafx.h"
#include "Poststring.h"

void Poststring::GeneratePOSTData()
{
	prefixhost = "host=";
	prefixip = "ip=";
	prefixmac = "mac=";
	prefixvlan = "vlan=";
	prefixswPort = "swPort=";
	prefixswName = "swName=";
	prefixswIP = "swIP=";
	prefixswMAC = "swMAC=";
	prefixsourceproto = "sp=";

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
	
	url = (char*)malloc((slhost + slip + slswPort + slvlan + slmac + slswName + slswIP + slswMAC + slsourceproto + 8 + 1) * sizeof(char));


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
	
}

char* Poststring::GeneratePOSTString(char* settingsServer, char* settingsPage)
{
	GeneratePOSTData();
	sprintf_s(postdata,
		"POST %s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"Content-Length: %i\r\n\r\n"
		"%s\r\n", settingsPage, settingsServer, strlen(url), url);
	return postdata;
}

void Poststring::addStrings(char** result, const char* prefix, const char* body, int& prefixlength, int& bodylength)
{
	*result = (char*)malloc((prefixlength + bodylength + 1) * sizeof(char));
	memcpy(*result, prefix, prefixlength);
	memcpy(*result + prefixlength, body, bodylength);
	(*result)[prefixlength + bodylength] = '\0'; //Must be set like this as array notation takes precendence over a dereferencing
	prefixlength = strlen(*result);
}

char Poststring::postdata[512] = {};
char Poststring::systemip[32] = {};
int Poststring::slsystemip = 0;
char* Poststring::prefixip = NULL;
	char* Poststring::ip = NULL;

	char Poststring::systemhostname[64] = {};
	int Poststring::slsystemhostname = 0;
	char* Poststring::prefixhost = NULL;
	char* Poststring::host = NULL;

	char Poststring::systemvlan[32] = {};
	int Poststring::slsystemvlan = 0;
	char* Poststring::prefixvlan = NULL;
	char* Poststring::vlan = NULL;

	char Poststring::systemswitchport[32];
	int Poststring::slsystemswitchport = 0;
	char* Poststring::prefixswPort = NULL;
	char* Poststring::swPort = NULL;

	char Poststring::systemswName[32];
	int Poststring::slsystemswName = 0;
	char* Poststring::prefixswName = NULL;
	char* Poststring::swName = NULL;

	char Poststring::systemmac[18] = {};
	int Poststring::slsystemmac = 0;
	char* Poststring::prefixmac = NULL;
	char* Poststring::mac = NULL;

	char Poststring::systemswIP[64] = {};
	int Poststring::slsystemswIP = 0;
	char* Poststring::prefixswIP = NULL;
	char* Poststring::swIP = NULL;

	char Poststring::systemswMAC[32] = {};
	int Poststring::slsystemswMAC = 0;
	char* Poststring::prefixswMAC = NULL;
	char* Poststring::swMAC = NULL;

	char Poststring::systemsourceproto[5] = {};
	int Poststring::slsystemsourceproto = 0;
	char* Poststring::prefixsourceproto = NULL;
	char* Poststring::sourceproto = NULL;

	char* Poststring::url = NULL;
