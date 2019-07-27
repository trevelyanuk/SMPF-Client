#pragma once

/* Flags for packet validation */
#define NO_MAC			1
#define NO_IP			2
#define NO_NAME			4 
#define NO_VLAN			8 
#define NO_PORT			16
#define IS_TELEPHONE	32
#define NOT_SWITCH		64

#define LLDP 0x0180c2 //0x88cc
#define CDP 0x01000c //0x2000

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
