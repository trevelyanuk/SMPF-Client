#pragma once

//CDP TLV headers 

#define CDP_TLV_DEVID           0x0001
#define CDP_TLV_ADDRESS         0x0002
#define CDP_TLV_PORTID          0x0003
#define CDP_TLV_CAPS            0x0004
#define CDP_TLV_VERS            0x0005
#define CDP_TLV_PLATFORM        0x0006
#define CDP_TLV_IPPREFIX        0x0007
#define CDP_TLV_HELLO           0x0008
#define CDP_TLV_VTPDOMAIN       0x0009
#define CDP_TLV_NATIVEVLAN      0x000A
#define CDP_TLV_DUPLEX          0x000B
#define CDP_TLV_VLREPLY         0x000E
#define CDP_TLV_VLQUERY         0x000F
#define CDP_TLV_POWER           0x0010
#define CDP_TLV_MTU             0x0011
#define CDP_TLV_TRUST_BITMAP    0x0012
#define CDP_TLV_UNTRUSTED_COS   0x0013
#define CDP_TLV_SYSTEM_NAME     0x0014
#define CDP_TLV_SYSTEM_OID      0x0015
#define CDP_TLV_MANAGEMENT_ADDR 0x0016
#define CDP_TLV_LOCATION        0x0017
#define CDP_TLV_EXT_PORTID      0x0017
#define CDP_TLV_POWER_REQUESTED 0x0018
#define CDP_TLV_POWER_AVAILABLE 0x0019
#define CDP_TLV_UNIDIR          0x001B

#define CDP_CAP_ROUTER					0x01    
#define CDP_CAP_TBBRIDGE				0x02
#define CDP_CAP_SPBRIDGE				0x04
#define CDP_CAP_SWITCH					0x08
#define CDP_CAP_HOST					0x10
#define CDP_CAP_IGMPFILTER				0x20
#define CDP_CAP_REPEATER				0x40
#define CDP_CAP_PHONE					0x80
#define CDP_CAP_REMOTELY_MANAGED_DEVICE	0x0100
#define CDP_CAP_CVTA 					0x0200 //Cast phone port, STP dispute resolution.. who knows..
#define CDP_CAP_TWO_PORT_MAC_RELAY 		0x0400