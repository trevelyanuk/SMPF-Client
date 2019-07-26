#pragma once

//LLDP TLV Headers
#define LLDP	0x88cc

/*

Type and length = 2 octets (7 and 9 bits)
Value is accomodated up to 511

Only 1 - 3 are required. 0 is also required, but doesnt always seem to be included..
We are therefore only guaranteed the port ID and the switch ID.
*VLAN and management address can't be guaranteed*

TLV Type		TLV Name				Mandatory		Structure
0				End of LLDPDU			Yes				TL
1				Chassis ID				Yes				TL	Chassis subtype (1)	Value (<255)
2				Port ID					Yes				TL	Port ID subtype (1)	Value (<255)
3				Time to live			Yes				TL	Value(2)

4				Port description		No				TL	Value (<255)
5				System name				No				TL	Value (<255)
6				System description		No				TL	Value (<255)
7				System capabilities		No				TL	System capabilities (2)	Enabled capabilities(2)
8				Management address		No				TL	Address length (1)	Address subtype (1)		Address (<31)
Interface numbering subtype (1)		Interface number (4)	OID string length (1) OID(<128)

9 - 126			Reserved				Reserved
127				*Organisation-specific*	No
*/

//LLDP TLV headers
#define LLDP_END			0
#define LLDP_CHASSIS_ID		1
#define LLDP_PORT_ID		2
#define LLDP_TTL			3
#define LLDP_PORT_DESC		4
#define LLDP_SYSTEM_NAME	5
#define LLDP_SYSTEM_DESC	6
#define LLDP_SYSTEM_CAP		7
#define LLDP_MGMT_ADDR		8
#define LLDP_ORG_SPEC		127

/*
Chassis subtype

Only one of these should exist and it should be the first TLV you can expect to find.
This is the physical unit that is attached to on the other end
The first byte after the TLV indicates the subtype

0	Reserved				—
1	Chassis component		"EntPhysicalAlias when entPhysClass has a value of
‘chassis(3)’(IETF RFC 4133)"
2	Interface alias			IfAlias(IETF RFC 2863)
3	Port component			"EntPhysicalAlias when entPhysicalClass has a value
‘port(10)’ or ‘backplane(4)’(IETF RFC 4133)"
4	MAC address				"MAC address(IEEE Std 802)"
5	Network address			IP address
6	Interface name			"ifName(IETF RFC 2863)"
7	Locally assigned		local (alphanumeric, locally assigned)
8–255 Reserved
*/
#define LLDP_CHASSIS_RESERVED		0
#define LLDP_CHASSIS_COMP			1
#define LLDP_CHASSIS_IFALIAS		2
#define LLDP_CHASSIS_PORTCOMP		3
#define LLDP_CHASSIS_MAC			4
#define LLDP_CHASSIS_IP				5
#define LLDP_CHASSIS_IFNAME			6
#define LLDP_CHASSIS_LOCALAS		7

/*
Port subtype 

Only one of these should exist and should be the second TLV
This is the port that this is connected to
The first byte after the TLV indicates the subtype

0		Reserved				—
1		Interface alias			ifAlias (IETF RFC 2863)
2		Port component			entPhysicalAlias when entPhysicalClass has a value
‘port(10)’ or ‘backplane(4)’ (IETF RFC 4133)
3		MAC address				MAC address (IEEE Std 802)
4		Network address			IP address
5		Interface name			ifName (IETF RFC 2863)
6		Agent circuit ID		agent circuit ID (IETF RFC 3046)
7		Locally assigned		local (alphanumeric, locally assigned)
8–255	Reserved
*/
#define LLDP_PORT_RESERVED		0
#define LLDP_PORT_IFALIAS		1
#define LLDP_PORT_PORTCOMP		2
#define LLDP_PORT_MAC			3
#define LLDP_PORT_IP			4
#define LLDP_PORT_IFNAME		5
#define LLDP_PORT_ACIRCID		6
#define LLDP_PORT_LOCALAS		7

/*
Capabilities subtype

Only one of these should exist
The first two octets are what capabilities the system has and the second are what it has *enabled*
The IEEE spec is wrong (page 31) as it suggests a chassis ID subtype!
Note that the left column is the BIT - so the final integer is a combination of all of these

1		Other								—
2		Repeater							IETF RFC 2108
3		MAC Bridge							IEEE Std 802.1D
4		WLAN Access Point					IEEE Std 802.11 MIB
5		Router								IETF RFC 1812
6		Telephone							IETF RFC 4293
7		DOCSIS cable device					IETF RFC 4639 and IETF RFC 4546
8		Station Only						(wont be used with any others) IETF RFC 4293
9		C-VLAN Component of a VLAN Bridge	IEEE Std 802.1Q
10		S-VLAN Component of a VLAN Bridge	IEEE Std 802.1Q
11		Two-port MAC Relay (TPMR)			IEEE Std 802.1Q
12–16	reserved
*/
#define LLDP_CAPS_OTHER			1
#define LLDP_CAPS_REPEATER		2
#define LLDP_CAPS_MAC_BRIDGE	4
#define LLDP_CAPS_WLAN_AP		8
#define LLDP_CAPS_ROUTER		16
#define LLDP_CAPS_TELEPHONE		32
#define LLDP_CAPS_DOCSIS		64
#define LLDP_CAPS_STATION		128
#define LLDP_CAPS_CVLAN			256
#define LLDP_CAPS_SVLAN			512
#define LLDP_CAPS_MAC_RELAY		1024

/*
Management address subtype

Only one of these should exist
The first octet gives the length of the management address subtype and management address fields together, in octets.
The subtype is going to be 1 octet, so the address is one less than the combined value. The address is likely an IP.
*/

/* from IETF RFC 3232, ianaAddressFamilyNumbers module */
#define LLDP_ADDR_IP4			1
#define LLDP_ADDR_IP6			2
