#pragma once

class Dissectors {
	typedef unsigned char  u_char;

	public:
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

		static int GetDataCDP(const u_char* packetData, int dataLength);
		static int GetDataLLDP(const u_char* packetData, int dataLength);

		static IndexValue lldp_tlv_type[10];
		static IndexValue cdp_tlv_type[32];
};
