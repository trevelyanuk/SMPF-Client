#pragma once
#include "stdafx.h"
#include "dissectors.h"


Dissectors::IndexValue Dissectors::lldp_tlv_management_subtype[31] = {
	{ 0x00, NULL },
	{ 0x01, "IPv4" },
	{ 0x02, "IPv6" },
	{ 0x03, "NSAP" },
	{ 0x04, "HDLC" },
	{ 0x05, "BBN" },
	{ 0x06, "802" },
	{ 0x07, "E.163" },
	{ 0x08, "E.164" },
	{ 0x09, "F.69" },
	{ 0x0a, "X.121" },
	{ 0x0b, "IPX" },
	{ 0x0c, "Appletalk" },
	{ 0x0d, "Decnet IV" },
	{ 0x0e, "Banyan Vines" },
	{ 0x0f, "E.164 with NSAP" },
	{ 0x10, "DNS" },
	{ 0x11, "Distinguished Name" },
	{ 0x12, "AS Number" },
	{ 0x13, "XTP over IPv4" },
	{ 0x14, "XTP over IPv6" },
	{ 0x15, "XTP native mode XTP" },
	{ 0x16, "Fiber Channel World-Wide Port Name" },
	{ 0x17, "Fiber Channel World-Wide Node Name" },
	{ 0x18, "GWID" },
	{ 0x19, "AFI for L2VPN" },
	{ 0x1a, "MPLS-TP Section Endpoint ID" },
	{ 0x1b, "MPLS-TP LSP Endpoint ID" },
	{ 0x1c, "MPLS-TP Pseudowire Endpoint ID" },
	{ 0x1d, "MT IP Multi-Topology IPv4" },
	{ 0x1e, "MT IP Multi-Topology IPv6"}
};

Dissectors::IndexValue Dissectors::lldp_tlv_chassis_subtype[8] = {
	{ 0, "Reserved" },
	{ 1, "Chassis component" },
	{ 2, "Interface alias" },
	{ 3, "Port component" },
	{ 4, "MAC address" },
	{ 5, "Network address" },
	{ 6, "Interface name" },
	{ 7, "Locally assigned" }
};

Dissectors::IndexValue Dissectors::lldp_tlv_port_subtype[8] = {
	{ 0, "Reserved" },
	{ 1, "Interface alias" },
	{ 2, "Port component" },
	{ 3, "MAC address" },
	{ 4, "Network address" },
	{ 5, "Interface name" },
	{ 6, "Agent circuit Id" },
	{ 7, "Locally assigned" }
};

Dissectors::IndexValue Dissectors::lldp_tlv_8021_subtype[17] = {
	{ 0x00, NULL },
	{ 0x01,	"Port VLAN ID" },
	{ 0x02, "Port and Protocol VLAN ID" },
	{ 0x03, "VLAN Name" },
	{ 0x04, "Protocol Identity" },
	{ 0x05, "VID Usage Digest" },
	{ 0x06, "Management VID" },
	{ 0x07,	"Link Aggregation" },
	{ 0x08,	"Congestion Notification" },
	{ 0x09, "ETS Configuration" },
	{ 0x0A, "ETS Recommendation" },
	{ 0x0B, "Priority Flow Control Configuration" },
	{ 0x0C, "Application Protocol" },
	{ 0x0D, "EVB" },
	{ 0x0E, "CDCP" },
	{ 0x0F, "Port extension" },
	{ 0x10, "Application VLAN" }
};

Dissectors::IndexValue Dissectors::lldp_tlv_8023_subtype[8] = {
	{ 0, NULL },
	{ 0x01,	"MAC/PHY Configuration/Status" },
	{ 0x02,	"Power Via MDI" },
	{ 0x03,	"Link Aggregation" },
	{ 0x04,	"Maximum Frame Size" },
	{ 0x05,	"EEE (Energy-Efficient Ethernet)" },
	{ 0x06,	"Unknown" },
	{ 0x07,	"IEEE 802.3br Additional Ethernet capabilities" }
};

Dissectors::IndexValue Dissectors::lldp_tlv_type[10] =
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
	{ LLDP_ORG_SPEC, "Organisation-specific TLV" },
};

Dissectors::IndexValue Dissectors::cdp_tlv_type[32] =
{
	{ 0x00, NULL },
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
	{ 0x0c, "Unknown" },
	{ 0x0d, "Unknown" },
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
	{ 0x18, "Unknown" },
	{ 0x19, "Power Requested" },
	{ 0x1a, "Power Available" },
	{ 0x1b, "Port Unidirectional" },
	{ 0x1c, "Unknown" },
	{ 0x1d, "Energywise" },
	{ 0x1e, "Unknown" },
	{ 0x1f, "Spare Pair POE" }
};

int Dissectors::GetDataCDP(const u_char* packetData, int dataLength)
{
	unsigned char validation = (NO_MAC | NO_IP | NO_NAME | NO_VLAN | NO_PORT | NOT_SWITCH);
	unsigned int count = 26;
	for (count; count < dataLength; )
	{
		unsigned int type = (packetData[count] << 8 | packetData[count + 1]);
		unsigned int length = (packetData[count + 2] << 8 | packetData[count + 3]); //length of the TLV - includes the type and length bytes themselves
		unsigned char value[512] = "";
		//length = length & mask;
		count += 4;
		length -= 4;

		for (UINT16 x = 0; x < length; x++)
		{
			value[x] = packetData[count];
			count++;
		}
		printf("\n\t%s: %s", cdp_tlv_type[type].value, value);

		switch (type)
		{
			case 0x01: //Device ID
			{
				memcpy(&Poststring::systemswName, packetData + count-length, length);
				Poststring::slsystemswName = strlen(Poststring::systemswName);
				validation &= ~NO_NAME;
				break;
			}
			case 0x02: //Address
			{
				long numberOfAddresses = (value[0] << 24 | value[1] << 16 | value[2] << 8 | value[3]);
				int tempCount = 4;
				for (UINT16 addressIndex = 0; addressIndex < numberOfAddresses; addressIndex++)
				{
					//Protocol type and length
					tempCount += 2;

					//This is an IP address
					if (value[tempCount] == 0xcc)
					{
						printf("IP Address: ");
						tempCount++;

						//This is how long it is
						int addressLength = (value[tempCount] << 8 | value[tempCount + 1]);
						tempCount += 2;

						sprintf_s(Poststring::systemswIP, "%i.%i.%i.%i", value[tempCount], value[tempCount + 1], value[tempCount + 2], value[tempCount + 3]);
						printf(Poststring::systemswIP);
						Poststring::slsystemswIP = strlen(Poststring::systemswIP);
						validation &= ~NO_IP;
						tempCount += addressLength;
					}
				}
				break;
			}
			case 0x03: //Port ID
			{
				memcpy(&Poststring::systemswitchport, value, length);
				Poststring::slsystemswitchport = strlen(Poststring::systemswitchport);
				validation &= ~NO_PORT;
				break;
			}
			case 0x04: //Capabilities
			{
				int syscaps = (value[0] << 24 | value[1] << 16| value[2] << 8 | value[3]);
				
				if (CDP_CAP_SWITCH & syscaps)
				{
					printf("This system is a switch.");

					validation &= ~NOT_SWITCH;
				}
				if ((CDP_CAP_PHONE & syscaps) || (CDP_CAP_HOST & syscaps))
				{
					printf("This system is a telephone.");

					validation |= IS_TELEPHONE;
				}
				break; 
			}
			case 0x05: break; //Version string, can be quite long 
			case 0x06: //Platform
			{
				memcpy(&Poststring::systemswMAC, value, length);
				Poststring::slsystemswMAC = strlen(Poststring::systemswMAC);
				validation &= ~NO_MAC;
				break;
			}
			case 0x07: break; //Prefixes
			case 0x08: break; //Protocol-hello option
			case 0x09: break; //VTP Management domain
			case 0x0a:  //Native VLAN ID
			{
				int port_vlan = (value[0] << 8 | value[1]);
				printf("%i", port_vlan);
				_itoa_s(port_vlan, Poststring::systemvlan, 10);
				Poststring::slsystemvlan = strlen(Poststring::systemvlan);
				validation &= ~NO_VLAN;
				break;
			}
			case 0x0b: break; //Duplex
			case 0x0c: break;
			case 0x0d: break;
			case 0x0e: break; //ATA - 186 VoIP VLAN request
			case 0x0f: break; //ATA-186 VoIP VLAN assignment
			case 0x10: break; //Power Consumption
			case 0x11: break; //MTU
			case 0x12: break; //AVVID Trust bitmap
			case 0x13: break; //AVVID Untrusted Ports CoS
			case 0x14: break; //System Name
			case 0x15: break; //System Object ID?
			case 0x16: break; //Management Address
			case 0x17: break; //Location - physical location?
			case 0x18: break; //Unknown
			case 0x19: break; //Power requested
			case 0x1a: break; //Power available
			case 0x1b: break; //Port Unidirectional
			case 0x1c: break; //Unknown
			case 0x1d: break; //Energywise
			case 0x1e: break; //Unknown
			case 0x1f: break; //Spare POE
			default:
			{
				printf("\n\n\t *** Unknown *** value = %s", value);
				break;
			}
		}
	}
	return validation;
}

int Dissectors::GetDataLLDP(const u_char* packetData, int dataLength)
{
	unsigned char validation = (NO_MAC | NO_IP | NO_NAME | NO_VLAN | NO_PORT | NOT_SWITCH);
	unsigned int count = 14; //LLDP starts at byte 14, after the mac addresses and type
	int mask = 0x01FF;

	//Each TLV type and length is 7 and 9 bits, respectively.
	for (count = 14; count < dataLength; )
	{
		unsigned char type = (packetData[count] >> 1);							//To get the type, you can bitshift by one place
		unsigned int length = (packetData[count] << 8 | packetData[count + 1]); //The length needs both bytes						
		unsigned char value[512] = "";
		length = length & mask;													//The length also needs a mask, to ignore the first 7 bits
		count += 2;

		char* typeString;
		(type == LLDP_ORG_SPEC) ? typeString = lldp_tlv_type[9].value : typeString = lldp_tlv_type[type].value;

		printf("\n\tType: %s, Length: %i", typeString, length);

		switch (type)
		{
			case LLDP_END: break;
			case LLDP_CHASSIS_ID:
			{
				int subtype = packetData[count];
				printf(", Subtype: %i", subtype);
				printf("\n\t\t%s:\t", lldp_tlv_chassis_subtype[subtype].value);
				count += 1;
				length -= 1;
				switch (subtype) {
					case LLDP_CHASSIS_RESERVED: break;
					case LLDP_CHASSIS_COMP: break;
					case LLDP_CHASSIS_IFALIAS: break;
					case LLDP_CHASSIS_PORTCOMP: break;
					case LLDP_CHASSIS_MAC:
					{
						sprintf_s(Poststring::systemswMAC, "%02x:%02x:%02x:%02x:%02x:%02x", packetData[count], packetData[count + 1], packetData[count + 2], packetData[count + 3], packetData[count + 4], packetData[count + 5]);
						printf(Poststring::systemswMAC);
						Poststring::slsystemswMAC = strlen(Poststring::systemswMAC);
						validation &= ~NO_MAC;
						break;
					}
					case LLDP_CHASSIS_IP:
					{
						char chassis_ip[16];
						int network_family = packetData[count];
						if (network_family == 1) //IPv4
						{
							sprintf_s(chassis_ip, "%i.%i.%i.%i", packetData[count + 1], packetData[count + 2], packetData[count + 3], packetData[count + 4]);
							printf(chassis_ip);
						}
						break;
					}
					case LLDP_CHASSIS_IFNAME:
					{
						for (UINT16 x = 0; x < length; x++)
						{
							value[x] = packetData[count + x];
						}
						printf("%s", value);
						break;
					}
					case LLDP_CHASSIS_LOCALAS: break;
				}
				count += length;
				break;
			}
			case LLDP_PORT_ID:
			{
				int subtype = packetData[count];
				printf(", Subtype: %i", subtype);
				printf("\n\t\t%s:\t", lldp_tlv_port_subtype[subtype].value);
				count += 1;
				length -= 1;
				switch (subtype)
				{
					case LLDP_PORT_RESERVED: break;
					case LLDP_PORT_IFALIAS: break;
					case LLDP_PORT_PORTCOMP: break;
					case LLDP_PORT_MAC: 
					{
						printf(" %02x:%02x:%02x:%02x:%02x:%02x",
							packetData[count], packetData[count + 1], packetData[count + 2], packetData[count + 3], packetData[count + 4], packetData[count + 5]);
						break;
					}
					case LLDP_PORT_IP: break;
					case LLDP_PORT_IFNAME:
					{
						for (UINT16 x = 0; x < length; x++)
						{
							value[x] = packetData[count + x];
						}
						printf("%s", value);
						break;
					}
					case LLDP_PORT_ACIRCID: break;
					case LLDP_PORT_LOCALAS:
					{
						for (UINT16 x = 0; x < length; x++)
						{
							value[x] = packetData[count + x];
						}
						printf("%s", value);
					}
					default: break;
				}

				count += length;
				break;
			}
			case LLDP_TTL:
			{
				printf("\n\t\t\tSeconds: %i ", (packetData[count] << 8 | packetData[count + 1]));
				count += 2;
				break;
			}
			case LLDP_PORT_DESC:
			{
				memcpy(&Poststring::systemswitchport, packetData + count, length);
				Poststring::slsystemswitchport = strlen(Poststring::systemswitchport);
				printf("\n\t\t%s", Poststring::systemswitchport);
				validation &= ~NO_PORT;
				count += length;
				break;
			}
			case LLDP_SYSTEM_NAME:
			{
				memcpy(&Poststring::systemswName, packetData + count, length);
				Poststring::slsystemswName = strlen(Poststring::systemswName);
				printf("\n\t\t%s", Poststring::systemswName);
				validation &= ~NO_NAME;
				count += length;
				break;
			}
			case LLDP_SYSTEM_DESC:
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count+x];
				}
				printf("\n\t\t%s", value);
				count += length;
				break;
			}
			case LLDP_SYSTEM_CAP:
			{
				int syscaps = (packetData[count] << 8 | packetData[count + 1]);
				int enacaps = (packetData[count + 2] << 8 | packetData[count + 3]);
				count += 4;
				length -= 4;

				printf("\n\t\tCapabilities:");

				if (LLDP_CAPS_OTHER & syscaps)
				{
					printf("\n\t\t\tThis system is something else..");
				}
				if (LLDP_CAPS_REPEATER & syscaps)
				{
					printf("\n\t\t\tThis system is a repeater.");
				}
				if (LLDP_CAPS_MAC_BRIDGE & syscaps)
				{
					printf("\n\t\t\tThis system is a switch.");

					validation &= ~NOT_SWITCH;
				}
				if (LLDP_CAPS_WLAN_AP & syscaps)
				{
					printf("\n\t\t\tThis system is a wireless access point.");
				}
				if (LLDP_CAPS_ROUTER & syscaps)
				{
					printf("\n\t\t\tThis system is a router.");
				}
				if (LLDP_CAPS_TELEPHONE & syscaps)
				{
					printf("\n\t\t\tThis system is a telephone.");

					validation |= IS_TELEPHONE;
				}
				if (LLDP_CAPS_DOCSIS & syscaps)
				{
					printf("\n\t\t\tThis system is a DOCSIS cable device.");
				}
				if (LLDP_CAPS_STATION & syscaps)
				{
					printf("\n\t\t\tThis system is a station.");
				}
				if (LLDP_CAPS_CVLAN & syscaps)
				{
					printf("\n\t\t\tThis system is a C-VLAN Component of a VLAN Bridge.");
				}
				if (LLDP_CAPS_SVLAN & syscaps)
				{
					printf("\n\t\t\tThis system is a S-VLAN Component of a VLAN Bridge.");
				}
				if (LLDP_CAPS_MAC_RELAY & syscaps)
				{
					printf("\n\t\t\tThis system is a two-port MAC relay.");
				}
				break;
		}
			case LLDP_MGMT_ADDR:
			{
				int sublength = packetData[count];
				int subtype = packetData[count+1];
				count += 2;
				length -= 2;
				printf("\n\t\tSubtype:\t%s (length:%i)", lldp_tlv_management_subtype[subtype].value, sublength);

				switch (subtype)
				{
					case LLDP_ADDR_IP4: //IPv4
					{
						sprintf_s(Poststring::systemswIP, "%i.%i.%i.%i", packetData[count], packetData[count + 1], packetData[count + 2], packetData[count + 3]);
						Poststring::slsystemswIP = strlen(Poststring::systemswIP);
						printf("\n\tIP address:\t%s", Poststring::systemswIP);
						validation &= ~NO_IP;
						count += 4;
						break;
					}
					default: break;
				}
	
				printf("\n\t\tInterface subtype: %i", packetData[count]);
				printf("\n\t\tInterface number: %lu", (packetData[count +1] << 24 | packetData[count + 2] << 16 | packetData[count + 3] << 8 | packetData[count + 4]));
				int oidLength = packetData[count +5];
				printf("\n\t\tOID Length: %i", oidLength);
				count += 6;

				if (oidLength > 0)
				{
					for (int j = 0; j < oidLength; j++)
						printf("\n\tOID: %i", packetData[count]);
					count++;
				}

				break;
		}
			case LLDP_ORG_SPEC:
			{
				long oui_id = (packetData[count] << 16 | packetData[count + 1] << 8 | packetData[count + 2]);
				int subtype = packetData[count + 3];
				printf("\n\t\tOUI: %02x-%02x-%02x", packetData[count], packetData[count + 1], packetData[count + 2]);
				printf("\n\t\tSubtype:\t %i", subtype);

				count += 4;
				length -= 4;

				switch (oui_id)
				{
					case 0x0012bb:
					{
						printf("\n\t\tTIA TR-41 Committee - %s", lldp_tlv_8021_subtype[subtype].value);

						switch (subtype)
						{
							case 0x0a:
							{
								memcpy(&Poststring::slsystemswName, packetData + count, length);
								Poststring::slsystemswName = strlen(Poststring::systemswName);
								validation &= ~NO_NAME;
								break;
							}
							default:
							{
								for (UINT16 x = 0; x < length; x++)
								{
									value[x] = packetData[count + x];
								}
								break;
							}
						}						
						count += length;
						break;
					}
					case 0x0080c2:
					{
						printf("\n\tIEEE 802.1 - %s", lldp_tlv_8021_subtype[subtype].value);
						switch (subtype)
						{
							case 1:
							{
								int port_vlan = (packetData[count] << 8 | packetData[count + 1]);
								printf(": %i", port_vlan);
								_itoa_s(port_vlan, Poststring::systemvlan, 10);
								Poststring::slsystemvlan = strlen(Poststring::systemvlan);
								validation &= ~NO_VLAN;
								break;
							}
							default: break;
						}
						count += length;
						break;
					}
					case 0x00120f:
					{
						//802.1AB-2009
						//Annex F for the layout
						printf("\n\t\tIEEE 802.3 - %s", lldp_tlv_8023_subtype[subtype].value);

						switch (subtype)
						{
							case 1:
							{
								//Octet 1 - bits 0 and 1 are the only ones important. This should never be greater than "3"
								printf("\n\t\t Auto-negotiation support: %i", (packetData[count] & 0x01)); //0xfe
								printf("\n\t\t Auto-negotiation status: %i", (packetData[count] & 0x02)); //0xfd
								printf("\n\t\t PMD auto-negotiation advertised capabilities: %i", (packetData[count + 1] << 8 | packetData[count + 2]));
								printf("\n\t\t Operational MAU type:%x", (packetData[count + 3] << 8 | packetData[count + 4]));
								break;
							}
							default:
							{
//								printf(" %i", (packetData[count] << 8 | packetData[count + 1]));
								for (UINT16 x = 0; x < length; x++)
								{
									value[x] = packetData[count + x];
								}
								printf("\n\t%s", value);
								break;
							}
						}
						count += length;
						break;
					}

					case 0x000142:
					{
						printf("\n\tCisco Systems, Inc");
						for (UINT16 x = 0; x < length; x++)
						{
							value[x] = packetData[count + x];
						}
						printf("\n\t%s", value);
						count += length;
					}
					default:
					{
						for (UINT16 x = 0; x < length; x++)
						{
							value[x] = packetData[count + x];
						}
						printf("\n\t%s", value);//, count - length);
						count += length;
						break;
					}
				}
				break;
			}
			default:
			{
				printf("\nUnknown");

				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count + x];
				}
				count += length;
				printf("\n\t%s", value);
				break;
			}
		}
	}
	return validation;
}