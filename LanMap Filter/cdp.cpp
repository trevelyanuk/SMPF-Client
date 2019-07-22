

//http://www.cisco.com/c/en/us/td/docs/ios-xml/ios/cdp/configuration/15-mt/cdp-15-mt-book/nm-cdp-discover.html


void getDataCDP()
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
	CDP uses Ethernet 1 headers, so bytes 12 and 13 are length
	*/
	printf("\n\tLength:\t\t %i", (packetData[12] << 8 | packetData[13]));

	/*
	CDP uses 802.2 LLC with SNAP headers, sp the next 8 bytes are LLC information, with SNAP extensions for Cisco:
	DSAP (1)
	SSAP (1)
	Control Field (1)

	(snap extension)
	OUI (3)
	Protocol ID (2)

	Bytes 14, 15, 16 are LLC
	Bytes 17, 18, 19 are the OUI (if its 0, then the PID is assumed to be the Ethertype, anything else indicates organisational specific things). Cisco is 0x00000c
	Bytes 20 and 21 are the Protocol ID, which will usually be EtherType. CDP is 2000 (0x2000)


	//https://www.informit.com/library/content.aspx?b=CCNP_Studies_Troubleshooting&seqNum=53
	//https://en.wikipedia.org/wiki/Subnetwork_Access_Protocol

	** CDP **


	For CDP, Bytes 22 and 23 are the version of CDP and the TTL
	24 and 25 are the checksum
	Anything beyond 23 is going to be TLV data. Last 4 octets will be the CRC Checksum, though
	*/

	printf("\n\t Cisco Discovery Protcol version %i\n\t TTL:%i", packetData[22], packetData[23]);


	//http://www.cisco.com/univercd/cc/td/doc/product/lan/trsrb/frames.htm is no longer available apparently, so I cant access it to find out the spec


	count = 26;

	for (count; count < packetHeader->len; )
	{


		unsigned int type = (packetData[count] << 8 | packetData[count + 1]);
		unsigned int length = (packetData[count + 2] << 8 | packetData[count + 3]); //length of the TLV - that includes the type and length itself!
																					//length = length & mask;
		count += 4;
		length -= 4;

		if (length > 500)
		{
			int k = 5;
		}

		unsigned char value[512] = "";

		switch (type)
		{
		case 0x01:
		{
			printf("\n\n\tDevice ID: ");

			memcpy(&systemswName, packetData + count, length);
			slsystemswName = strlen(systemswName);

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x02:
		{
			printf("\n\n\tAddress: ");

			//Number of addresses
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


					sprintf_s(systemswIP, "%i.%i.%i.%i", packetData[count], packetData[count + 1], packetData[count + 2], packetData[count + 3]);
					printf(systemswIP);
					slsystemswIP = strlen(systemswIP);
					count += addressLength;
				}

			}

			break;
		}
		case 0x03:
		{
			printf("\n\n\tPort-ID: ");

			memcpy(&systemswitchport, packetData + count, length);
			slsystemswitchport = strlen(systemswitchport);

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			break;
		}
		case 0x04:
		{
			printf("\n\n\tCapability: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x05:
		{
			printf("\n\n\tVersion String: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x06:
		{
			printf("\n\n\tPlatform: ");

			memcpy(&systemswMAC, packetData + count, length);
			slsystemswMAC = strlen(systemswMAC);
			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x07:
		{
			printf("\n\n\tPrefixes: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x08:
		{
			printf("\n\n\tProtocol-Hello option: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x09:
		{
			printf("\n\n\tVTP Management Domain: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x0a:
		{

			printf("\n\n\tNative VLAN ID: ");
			int port_vlan = (packetData[count] << 8 | packetData[count + 1]);

			//printf("VLAN ID: %i", port_vlan);
			_itoa_s(port_vlan, systemvlan, 10);
			slsystemvlan = strlen(systemvlan);

			count += 2;

			printf("%i", port_vlan);
			break;
		}
		case 0x0b:
		{
			printf("\n\n\tDuplex: ");

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
			printf("\n\n\tDONT KNOW LOL");

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
			printf("\n\n\tDONT KNOW LOL");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x0e:
		{
			printf("\n\n\tATA-186 VoIP VLAN request: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x0f:
		{
			printf("\n\n\tATA-186 VoIP VLAN assignment: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x10:
		{
			printf("\n\n\tPower Consumption: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x11:
		{
			printf("\n\n\tMTU: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x12:
		{
			printf("\n\n\tAVVID Trust Bitmap: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x13:
		{
			printf("\n\n\tAVVID Untrusted Ports CoS: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x14:
		{
			printf("\n\n\tSystem Name: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x15:
		{
			printf("\n\n\tSystem Object ID (Not Decoded): ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x16:
		{
			printf("\n\n\tManagement Addresses: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x17:
		{
			printf("\n\n\tPhysical Location: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x18:
		{
			printf("\n\n\tUNKNOWN: ");

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
			printf("\n\n\tUNKNOWN: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x1a:
		{
			printf("\n\n\tPower Available: ");

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
			printf("\n\n\tUNKNOWN: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x1c:
		{
			printf("\n\n\tUNKNOWN: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x1d:
		{
			printf("\n\n\tEnergyWise: ");

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
			printf("\n\n\tUNKNOWN: ");

			for (UINT16 x = 0; x < length; x++)
			{
				value[x] = packetData[count];
				count++;
			}
			printf("%s", value);//, count - length);
			break;
		}
		case 0x1f:
		{
			printf("\n\n\tSpare PoE: ");

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
}