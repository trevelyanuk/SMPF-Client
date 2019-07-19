#pragma once
#include "stdafx.h"

class Dissectors {
	typedef unsigned char   u_char;

	public:
		static int GetDataCDP(const u_char* packetData, int dataLength) {};
		static int GetDataLLDP(const u_char* packetData, int dataLength) {};
};
