# Switchy McPortFace (SMPF)
For want of a better name..

The SMPF client is an application that simply captures switch advertisements broadcast over a local wired network in order to determine information about the switch to which that host is connected, notably the *switch port* that the host is using. Whilst this is possible to do via SNMP or other switch management tools, SMPF aims to accomplish this solely from the hosts themselves. 

Once collected, this information can be output and viewed locally on a host, collected into a local log file, collected into a CSV or sent as POST data to a server. Information that is currently collected so far:
- Switch IP
- Switch name
- Switch MAC address
- Switch port
- Switch port VLAN
- Host IP 
- Host name
- Host MAC address
- Protocol that the data was captured using 

##Libraries
SMPF uses pcap at its core; namely WinPcap*(libpcap 1.0) on Windows or libpcap on Linux systems. This allows for layer 2 frames to be received by the operating system in promiscuous mode. 

*Note: Npcap 'should' be the way forward, but their license terms prohibit actual 'free' use currently, since it is capped at 5 systems.

##Protocols
The SMPF client creates a filter which allows through either CDP and/or LLDP frames. It would be interesting to be able to incorporate Juniper discovery protocol data, or other discovery protocols; however, LLDP is vendor-agnostic and is implemented nearly everywhere. These protocols are not usually used by host operating systems, since they're primarily for switches and routers to build a picture about their neighbours, although they are also leveraged by Fluke testing tools.

Its important to note that not all switches will have LLDP and CDP advertisements enabled, so you're likely out of luck if you don't have access to your network infrastructure in order to enable them (if they aren't already).

Contributions are welcome and I would be really interested to hear from anyone who has Juniper kit, or who wants to implement this or has issues with their own setup
