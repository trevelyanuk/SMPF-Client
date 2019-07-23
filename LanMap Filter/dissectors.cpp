#pragma once
#include "stdafx.h"
#include "dissectors.h"

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
	{ LLDP_ORG_SPEC, "Organisation-specific LLDP" },
};

Dissectors::IndexValue Dissectors::cdp_tlv_type[22] =
{
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
	{ 0, NULL }
};

int Dissectors::GetDataCDP(const u_char* packetData, int dataLength) 
{
	printf("\n\tDestination MAC address:\t %02x:%02x:%02x:%02x:%02x:%02x", packetData[0], packetData[1], packetData[2], packetData[3], packetData[4], packetData[5]);
	printf("\n\tSource MAC address:\t\t %02x:%02x:%02x:%02x:%02x:%02x", packetData[6], packetData[7], packetData[8], packetData[9], packetData[10], packetData[11]);
	printf("\n\tLength:\t\t %i", (packetData[12] << 8 | packetData[13]));
	printf("\n\tCisco Discovery Protcol version %i", packetData[22]);
	//printf("\n\tTTL:%i", packetData[23]);

	unsigned int count = 26;

	//Iterate through each TLV
	for (count; count < dataLength; )
	{
		unsigned int type = (packetData[count] << 8 | packetData[count + 1]);
		unsigned int length = (packetData[count + 2] << 8 | packetData[count + 3]); //length of the TLV - includes the type and length bytes themselves
		unsigned char value[512] = "";
		//length = length & mask;
		count += 4;
		length -= 4;
		
		printf("\n\t%s", cdp_tlv_type[type].value);
		switch (type)
		{
			case 0x01: //Device ID
			{
				memcpy(&Poststring::systemswName, packetData + count, length);
				Poststring::slsystemswName = strlen(Poststring::systemswName);

				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x02: //Address
			{
				long numberOfAddresses = (packetData[count] << 24 | packetData[count] << 16 | packetData[count + 2] << 8 | packetData[count + 3]);
				count += 4;
				length -= 4;
				for (UINT16 x = 0; x < numberOfAddresses; x++)
				{
					//Protocol type
					//Protocol length
					count += 2;

					//This is an IP address
					if (packetData[count] == 0xcc)
					{
						printf("IP Address: ");
						count++;

						//This is how long it is
						int addressLength = (packetData[count] << 8 | packetData[count + 1]);
						count += 2;


						sprintf_s(Poststring::systemswIP, "%i.%i.%i.%i", packetData[count], packetData[count + 1], packetData[count + 2], packetData[count + 3]);
						printf(Poststring::systemswIP);
						Poststring::slsystemswIP = strlen(Poststring::systemswIP);
						count += addressLength;
					}
				}
				break;
			}
			case 0x03: //Port ID
			{
				memcpy(&Poststring::systemswitchport, packetData + count, length);
				Poststring::slsystemswitchport = strlen(Poststring::systemswitchport);

				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				break;
			}
			case 0x04: //Capabilities
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x05: //Version string, can be quite long
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x06: //Platform
			{
				memcpy(&Poststring::systemswMAC, packetData + count, length);
				Poststring::slsystemswMAC = strlen(Poststring::systemswMAC);
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x07: //Prefixes
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x08: //Protocol-hello option
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x09: //VTP Management domain
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x0a: //Native VLAN ID
			{
				int port_vlan = (packetData[count] << 8 | packetData[count + 1]);

				//printf("VLAN ID: %i", port_vlan);
				_itoa_s(port_vlan, Poststring::systemvlan, 10);
				Poststring::slsystemvlan = strlen(Poststring::systemvlan);

				count += 2;

				printf("%i", port_vlan);
				break;
			}
			case 0x0b: //Duplex
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x0c:
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x0d:
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x0e: //ATA - 186 VoIP VLAN request
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x0f: //ATA-186 VoIP VLAN assignment
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x10: //Power Consumption
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x11: //MTU
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x12: //AVVID Trust bitmap
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x13: //AVVID Untrusted Ports CoS
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x14: //System Name
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x15: //System Object ID?
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x16: //Management Address
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x17: //Location - physical location?
			{	
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x18: //Unknown
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x19:
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x1a: //Power available
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x1b:
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x1c:
			{for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x1d: //Energywise
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x1e:
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			case 0x1f: //Spare POE
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("%s", value);//, count - length);
				break;
			}
			default:
			{
				printf("\n\n\t *** Unknown *** value = %s", value);
				break;
			}
		}
	}
	return 0;
}

int Dissectors::GetDataLLDP(const u_char* packetData, int dataLength)
{

	unsigned int count = 0;

	/*
	Destination MAC address - which is octet 0 - 5
	*/
	//%02x, rather than %x, will enforce a mininum field size - so a value of 1 becomes 01 and e becomes 0e. The 0 specifies that it should be 0 padded, the 2 represents the number of 0s.
	printf("\tDestination MAC address:\t %02x:%02x:%02x:%02x:%02x:%02x", packetData[0], packetData[1], packetData[2], packetData[3], packetData[4], packetData[5]);


	/*
	Source MAC address - which is octet 6 - 11
	*/
	printf("\n\tSource MAC address:\t\t %02x:%02x:%02x:%02x:%02x:%02x", packetData[6], packetData[7], packetData[8], packetData[9], packetData[10], packetData[11]);

	/*
	Ethertype is going to be 12 - 13, which we already know is LLDP to even get this far.
	*/

	/*
	Anything at octet 14 and beyond is going to be data. Last 4 octets will be the CRC Checksum, though
	*/
	printf("\n\tContents: ");


	//Ok so the next two octets are Type and Length - but the problem is that Type only takes up 7 bits, Length takes up 9
	//Bitwise time again
	//We can give "type" a value of one byte - so a char and tell it to use octet 14.. but shift that data one to the right.
	//This will mean that it will lose the lowest order bit.. but that is only used by the length anyway, so it doesn't matter
	//(actually it also doesnt matter if it is signed or not, we dont use the highest order bit)
	//That should make all 1s and 0s move one place along, which is what we want.
	//
	//Then the length can be two bytes - so an int (again, unsigned or not isnt too big a deal) - and this time, we assign two values, with one of the characters shifted by 8 bits to the left 
	//Both values will be stored, but we still have to remove 7 of 8 bytes of the upper half.
	//We can do this with a binary AND function, by creating a mask of the bits you do want 
	//An AND of this, with other values, would retain the value of the length up to a maximum value of 512 - which is what we want
	//so 00000001 11111111, or 01FF, would only allow values for the lowest 9 bits, discounting any values in the first 7

	count = 14;

	int mask = 0x01FF;

	for (count = 14; count < dataLength; )
	{

		unsigned char type = (packetData[count] >> 1);
		unsigned int length = (packetData[count] << 8 | packetData[count + 1]);
		length = length & mask;
		count += 2;

		//Either its an LLDP organisation-specific TLV..
		if (type == LLDP_ORG_SPEC)
		{

			printf("\n\n\tType:\t Organisational Specific (octet: %i)", count);
		}
		//Or it isn't
		else
		{
			printf("\n\n\tType:\t %s (type: %i, octet: %i)", lldp_tlv_type[type].value, type, count);
		}



		printf("\n\tLength:\t %u (octet: %i)", length, count);




		//Max value
		unsigned char value[512] = "";


		switch (type)
		{

			//End of packet!
		case LLDP_END:
		{
			return 0;
		}

		/*
		Chassis subtype

		Only one of these should exist and it should be the first TLV you can expect to find.
		This is the physical unit that is attached to on the other end
		The first byte after the TLV indicates the subtype
		*/
		case LLDP_CHASSIS_ID:
		{
			int subtype = packetData[count];
			count += 1;
			length -= 1;
			if (subtype == LLDP_CHASSIS_RESERVED)
			{
			}
			if (subtype == LLDP_CHASSIS_COMP)
			{
			}
			if (subtype == LLDP_CHASSIS_IFALIAS)
			{
			}
			if (subtype == LLDP_CHASSIS_PORTCOMP)
			{
			}
			if (subtype == LLDP_CHASSIS_MAC)
			{
				sprintf_s(Poststring::systemswMAC, "%02x:%02x:%02x:%02x:%02x:%02x", packetData[count], packetData[count + 1], packetData[count + 2], packetData[count + 3], packetData[count + 4], packetData[count + 5]);
				printf("\n\tMAC address:\n\t");
				printf(Poststring::systemswMAC);
				Poststring::slsystemswMAC = strlen(Poststring::systemswMAC);


				count += 6;
			}
			if (subtype == LLDP_CHASSIS_IP)
			{
			}
			if (subtype == LLDP_CHASSIS_IFNAME)
			{
				printf("\n\tInterface name:");

				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("\n\t%s", value);//, count - length);

			}
			if (subtype == LLDP_CHASSIS_LOCALAS)
			{
			}

			printf("\t (Subtype: %i)", subtype);
			break;
		}

		/*
		Port subtype

		Only one of these should exist and should be the second TLV
		This is the port that this is connected to
		The first byte after the TLV indicates the subtype
		*/
		case LLDP_PORT_ID:
		{
			int subtype = packetData[count];

			count += 1;
			length -= 1;
			if (LLDP_PORT_RESERVED == subtype)
			{
			}
			if (LLDP_PORT_IFALIAS == subtype)
			{
			}
			if (LLDP_PORT_PORTCOMP == subtype)
			{
			}
			if (LLDP_PORT_MAC == subtype)
			{
				printf("\n\tMAC address %02x:%02x:%02x:%02x:%02x:%02x",
					packetData[count], packetData[count + 1], packetData[count + 2], packetData[count + 3], packetData[count + 4], packetData[count + 5]);
				count += 6;
			}
			if (LLDP_PORT_IP == subtype)
			{
			}
			if (LLDP_PORT_IFNAME == subtype)
			{
				printf("\n\tInterface name:");


				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("\n\t%s", value);//, count - length);
			}
			if (LLDP_PORT_ACIRCID == subtype)
			{
			}
			if (LLDP_PORT_LOCALAS == subtype)
			{
				printf("\n\tLocally Assigned:");


				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("\n\t%s", value);//, count - length);
			}
			printf("\t (Subtype: %i)", subtype);
			break;
		}

		/*
		Only one of these should exist and it should be the third TLV
		*/
		case LLDP_TTL:
		{
			printf("\n\tTime to live: %i ", (packetData[count] << 8 | packetData[count + 1]));
			count += 2;
			break;
		}

		/*
		Only one of these should exist
		String indicating the port description on the other end of the link
		*/
		case LLDP_PORT_DESC:
		{
			//temp_switchport = packetData + count;
			//memcpy(&test, temp_switchport, 31);
			memcpy(&Poststring::systemswitchport, packetData + count, length);
			Poststring::slsystemswitchport = strlen(Poststring::systemswitchport);

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("\n\t%s", value);//, count - length);
			break;
		}

		/*
		Only one of these should exist
		String indicating the system's name on the other end of the link, which should be the FQDN
		*/
		case LLDP_SYSTEM_NAME:
		{
			memcpy(&Poststring::systemswName, packetData + count, length);
			Poststring::slsystemswName = strlen(Poststring::systemswName);

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("\n\t%s", value);//, count - length);
			break;
		}

		/*
		Only one of these should exist
		String indicating the system description on the other end of the link, which should include the name and version of the software, the hardware type, OS and network software
		*/
		case LLDP_SYSTEM_DESC:
		{

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("\n\t%s", value);//, count - length);

			break;
		}


		/*
		Capabilities subtype

		Only one of these should exist
		The first two octets are what capabilities the system has and the second are what it has *enabled*
		The IEEE spec is wrong (page 31) as it suggests a chassis ID subtype!
		Note that the left column is the BIT - so the final integer is a combination of all of these
		*/
		case LLDP_SYSTEM_CAP:
		{

			int syscaps = (packetData[count] << 8 | packetData[count + 1]);
			int enacaps = (packetData[count + 2] << 8 | packetData[count + 3]);
			count += 4;
			length -= 4;

			if (LLDP_CAPS_OTHER & syscaps)
			{
				printf("\n\tCapabilities: This system is something else..");
			}
			if (LLDP_CAPS_REPEATER & syscaps)
			{
				printf("\n\tCapabilities: This system is a repeater.");
			}
			if (LLDP_CAPS_MAC_BRIDGE & syscaps)
			{
				printf("\n\tCapabilities: This system is a switch.");
			}
			if (LLDP_CAPS_WLAN_AP & syscaps)
			{
				printf("\n\tCapabilities: This system is a wireless access point.");
			}
			if (LLDP_CAPS_ROUTER & syscaps)
			{
				printf("\n\tCapabilities: This system is a router.");
			}
			if (LLDP_CAPS_TELEPHONE & syscaps)
			{
				printf("\n\tCapabilities: This system is a telephone.");
				return 1;
			}
			if (LLDP_CAPS_DOCSIS & syscaps)
			{
				printf("\n\tCapabilities: This system is a DOCSIS cable device.");
			}
			if (LLDP_CAPS_STATION & syscaps)
			{
				printf("\n\tCapabilities: This system is a station.");
			}
			if (LLDP_CAPS_CVLAN & syscaps)
			{
				printf("\n\tCapabilities: This system is a C-VLAN Component of a VLAN Bridge.");
			}
			if (LLDP_CAPS_SVLAN & syscaps)
			{
				printf("\n\tCapabilities: This system is a S-VLAN Component of a VLAN Bridge.");
			}
			if (LLDP_CAPS_MAC_RELAY & syscaps)
			{
				printf("\n\tCapabilities: This system is a two-port MAC relay.");
			}

			break;
		}

		/*
		Management address subtype

		Only one of these should exist
		The first octet gives the length of the management address subtype and management address fields together, in octets.
		The subtype is going to be 1 octet, so the address is one less than the combined value. The address is likely an IP.
		*/

		case LLDP_MGMT_ADDR:
		{
			int sublength = packetData[count];

			count += 1;
			length -= 1;
			printf("\n\tSubtype length:%i", sublength);

			int subtype = packetData[count];

			count += 1;
			length -= 1;

			switch (subtype)
			{
			case LLDP_ADDR_IP4: //IPv4
			{
				sprintf_s(Poststring::systemswIP, "%i.%i.%i.%i", packetData[count], packetData[count + 1], packetData[count + 2], packetData[count + 3]);
				printf("\n\tIP address: ");
				printf(Poststring::systemswIP);
				Poststring::slsystemswIP = strlen(Poststring::systemswIP);

				count += 4;
				break;
			}
			case LLDP_ADDR_IP6:
			{
				break;
			}
			case LLDP_ADDR_NSAP:
			{
				break;
			}
			case LLDP_ADDR_HDLC:
			{
				break;
			}
			case LLDP_ADDR_BBN1822:
			{
				break;
			}
			case LLDP_ADDR_802:
			{
				break;
			}
			case LLDP_ADDR_E163:
			{
				break;
			}
			case LLDP_ADDR_E164:
			{
				break;
			}
			case LLDP_ADDR_F69:
			{
				break;
			}
			case LLDP_ADDR_X121:
			{
				break;
			}
			case LLDP_ADDR_IPX:
			{
				break;
			}
			case LLDP_ADDR_APPLETALK:
			{
				break;
			}
			case LLDP_ADDR_DECNET:
			{
				break;
			}
			case LLDP_ADDR_BANTANVINES:
			{
				break;
			}
			case LLDP_ADDR_E164_NSAP:
			{
				break;
			}
			case LLDP_ADDR_DNS:
			{
				break;
			}
			}


			/*
			Interface subtype
			1) Unknown
			2) ifIndex
			3) system port number

			*/

			printf("\n\t\tInterface subtype: %i", packetData[count]);
			count++;

			printf("\n\t\tInterface number: %lu", (packetData[count] << 24 | packetData[count + 1] << 16 | packetData[count + 2] << 8 | packetData[count + 3]));
			count += 4;

			int oidLength = packetData[count];
			printf("\n\t\tOID Length: %i", oidLength);
			count++;

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
			//So this is going to be one of the optional TLVs which could be absolutely anything.
			//The first three octets will be the OUI

			printf("\n\t\tOUI: %02x-%02x-%02x", packetData[count], packetData[count + 1], packetData[count + 2]);

			long oui_id = (packetData[count] << 16 | packetData[count + 1] << 8 | packetData[count + 2]);
			count += 3;

			int subtype = packetData[count];
			printf("\n\t\tSubtype:\t %i (octet: %i)", packetData[count], count);


			count += 1;
			length -= 4;

			switch (oui_id)
			{
			case 0x0012bb:
			{
				switch (subtype)
				{
				case 0x05:
				{
					memcpy(&Poststring::systemswMAC, packetData + count, length);
					Poststring::slsystemswMAC = strlen(Poststring::systemswMAC);
					count += length;
					break;
				}
				default:
				{
					for (UINT16 x = 0; x < length; x++)
					{
						value[x] = packetData[count];
						count++;
					}
					break;
				}
				}
				break;
			}
			case 0x0080c2:
			{
				printf("\n\tIEEE 802.1 - ");
				switch (subtype)
				{
				case 1:
				{
					int port_vlan = (packetData[count] << 8 | packetData[count + 1]);
					//printf("VLAN ID: %i", port_vlan);
					_itoa_s(port_vlan, Poststring::systemvlan, 10);
					Poststring::slsystemvlan = strlen(Poststring::systemvlan);
					count += 2;
					break;
				}
				case 2:
				{
					//	printf("VLAN ID: %i", (packetData[count] << 8 | packetData[count + 1]));
					count += 2;
					break;
				}
				default:
				{
					break;
				}
				}

				break;
			}
			case 0x00120f:
			{
				//802.1AB-2009
				//Annex F for the layout

				printf("\n\t\t IEEE 802.3 - ");


				switch (subtype)
				{
				case 1:
				{
					//F2.x
					printf("MAC/PHY Configuration/Status: ");

					//Octet 1 - bits 0 and 1 are the only ones important. This should never be greater than "3"
					printf("\n\t\t Auto-negotiation support: %i", (packetData[count] & 0x01)); //0xfe
					printf("\n\t\t Auto-negotiation status: %i", (packetData[count] & 0x02)); //0xfd
					count += 1;

					//Octet 2 and 3 - all bits are a value.

					printf("\n\t\t PMD auto-negotiation advertised capabilities: %i", (packetData[count] << 8 | packetData[count + 1]));
					count += 2;


					//Octet 4 and 5
					printf("\n\t\t Operational MAU type:%x", (packetData[count] << 8 | packetData[count + 1]));
					count += 2;
					break;
				}
				case 2:
				{
					printf("Power Via Medium Dependent Interface (MDI): %i", (packetData[count] << 8 | packetData[count + 1]));
					count += 2;
					break;
				}
				case 3:
				{
					printf("Link Aggregation (deprecated): %i", (packetData[count] << 8 | packetData[count + 1]));
					count += 2;
					break;
				}
				case 4:
				{
					printf("Maximum Frame Size: %i", (packetData[count] << 8 | packetData[count + 1]));
					count += 2;
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			default:
			{
				for (UINT16 x = 0; x < length; x++)
				{
					value[x] = packetData[count];
					count++;
				}
				printf("\n\t%s", value);//, count - length);
				break;
			}
			}
			break;
		}
		default:
		{
			printf("\nlol what am i");


			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("\n\t%s", value);//, count - length);
			break;
		}
		}
	}
	return 0;
}