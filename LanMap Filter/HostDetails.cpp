#include "stdafx.h"
#include "HostDetails.h"

class HostDetails {

	HostDetails::HostDetails()
	{
		GetHostIp();
		GetHostname();
		GetMACaddress();
	}

	//I hate that this has the same name as the WinSock gethostname and that its only case sensitivity that separates them!
	void HostDetails::GetHostname()
	{
#ifdef _WIN32
		GetHostnameWindows();
#endif 
#ifdef __linux__
		GetHostnameLinux();
#endif 
#ifdef __APPLE__
		GetHostnameApple();
#endif
	}
	void HostDetails::GetHostnameApple()
	{
		gethostname(systemhostname, 64);
		slsystemhostname = strlen(systemhostname);
	}
	void HostDetails::GetHostnameLinux()
	{
		gethostname(systemhostname, 64);
		slsystemhostname = strlen(systemhostname);
	}
	//explain this under "other useful stuff"
	void HostDetails::GetHostnameWindows()
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

	void HostDetails::GetMACaddress()
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
	void HostDetails::GetMACaddressApple()//pcap_if_t * addapter_correct)
	{
	}
	void HostDetails::GetMACaddressLinux()//pcap_if_t * addapter_correct)
	{
	}
	void HostDetails::GetMACaddressWindows()//pcap_if_t * addapter_correct)
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

				IsVirtualMacAddress(pAdapterInfo->Address);

				//%02x means hex (the x) and print in the format of having 2 characters. prefixes with a 0 if theres nothing
				printf("\nMac Address: %02x:%02x:%02x:%02x:%02x:%02x", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);


				_snprintf_s(systemmac, SZ_MAC, "%02x:%02x:%02x:%02x:%02x:%02x", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
				slsystemmac = strlen(systemmac);

			}
			pAdapterInfo = pAdapterInfo->Next;    // Progress through linked list
		} while (pAdapterInfo);                    // Terminate if last adapter
	}

	bool HostDetails::IsVirtualMacAddress(BYTE* addr)
	{
		//VMWare
			if ((addr[0] == 0x00) && (addr[1] == 0x50)  && (addr[2] == 0x56))
			{
				return true;
			}
			if ((addr[0] == 0x00) && (addr[1] == 0x0c) && (addr[2] == 0x29))
			{
				return true;
			}
		//XenSource
			if ((addr[0] == 0x00) && (addr[1] == 0x16) && (addr[2] == 0x3e))
			{
				return true;
			}
		//KVM
			if ((addr[0] == 0x52) && (addr[1] == 0x54) && (addr[2] == 0x00))
			{
				return true;
			}
		//Microsoft
			if ((addr[0] == 0x00) && (addr[1] == 0x03) && (addr[2] == 0xff))
			{
				return true;
			}
		//Virtual Iron
			if ((addr[0] == 0x00) && (addr[1] == 0x0f) && (addr[2] == 0x4b))
			{
				return true;
			}
		
		return false;
	}
};