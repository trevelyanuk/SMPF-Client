#pragma once
#include "stdafx.h"

class HostDetails
{
	public: 
		 HostDetails();
		~HostDetails() {};
		void GetHostIp();
	void GetHostnameWindows();
	void GetHostnameLinux();
	void GetHostnameApple();
	void GetHostname();
	void GetMACaddressWindows();
	void GetMACaddressLinux();
	void GetMACaddressApple();
	void GetMACaddress();
	bool IsVirtualMacAddress(BYTE*);
};

