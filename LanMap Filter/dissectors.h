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

		static IndexValue lldp_tlv_8023_subtype[8];
		static IndexValue lldp_tlv_8021_subtype[17];
		static IndexValue lldp_tlv_management_subtype[31];
		static IndexValue lldp_tlv_chassis_subtype[8];
		static IndexValue lldp_tlv_port_subtype[8];
		static IndexValue lldp_tlv_type[10];
		static IndexValue cdp_tlv_type[32];
};
