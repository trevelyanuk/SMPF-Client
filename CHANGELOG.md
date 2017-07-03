# Change log
## Current version - 0.3

* Issues
  * Only checks if a packet is CDP or LLDP, with no distinction for filtering packets destined for phones. Causes incorrect submissions of entries to database.
  * Fix adapters with retained IPs
  * Detect if wireless adapters are present and do not listen for packets on these adapters
  
* To do 
  * More debug info
  * Name project
  * Release build to have no interface at all (automated) unless run from command line
  * Create installer to bundle everything up
  * Create Mac and Linux builds
  * Create makefile and .sln files for distribution
  * Put it all on git or sourceforge
  * FOG module
  * Static link libraries
  * Tidy up screen output (\n in the right places) and ensure that debug and release have different behaviour
  * Tidy up LLDP TLVs
  * Tidy up CDP TLVs


## Change history   
### 2016-06-22
** Version 0.3 **

The client now can be set to output to a log file, rather than to upload data to a server

* To do 
  * Tidy up screen output (\n in the right places) and ensure that debug and release have different behaviour
  * Tidy up LLDP TLVs
  * Tidy up CDP TLVs

### 2016-06-06
** Version 0.2 **

cURL is no more! I have sped ahead and managed to cut this out entirely by using WinSock instead of cURL. This means that no extra DLL is needed on Windows, although for consistency on different platforms and SSL support, I may go back to using cURL later and focus on not using separate DLLs.

The server address in the config file now has the page, and the address, as separate items. This just makes it easier when sending the POST request to the server; cURL seemed to split this out (give it the full address, including http://, and it does internal magic to split that up as necessary) but this has to be done manually when working with sockets directly.

* Issues
  * Detect if wireless adapters are present and do not listen for packets on these adapters

* Fixed
  * Find out why CURL can be so slow
  * Replace CURL with native platform socket code


### 2016-05-26
** Version 0.1 ** 
System is now in use somewhere and tested on ~1500 Windows 7 computers. Version can now jump to 0.1

* Todo
  * Replace CURL with native platform socket code
  
### 2015-10-23
**Version 0.0.4**

An old (but new) update.

CDP packets are now internally formatted to be read as TLVs, based on Cisco's CDP standard (which is hard to find anywhere). Won't bother with any other protocols - if anywhere uses them, though, I can add them in one day.

Added cases for checking capture protocol used (CDP or LLDP) when uploading data and fixed some output formatting.

* Fixed
  * Create TLVs for CDP and other protocols
  * Use TLVs instead of currently "guessing" where data is
  
* Issues
  * It looks like adapters will retain their IP, even if they are inactive and have been disconnected. This can result in disconnected adapters being selected as the interface to listen on, even if they aren't connected.

### 2015-08-24
**Version 0.0.3**

LLDP packets are now internally formatted to be read as TLVs, based on IEEE 802.1AB/2009.

The output for text is now better formatted, too.

* To do
  * Use TLVs instead of currently "guessing" where data is
  * Create TLVs for CDP and other protocols



### 2015-05-02
**Version 0.0.2 (Also really really early)**

Mostly just adding a configuration file. Still lots that needs doing.

A configuration file has now been added. You can specify server address, timeout, whether to use LLDP and/or CDP and what the first octet of the network address is to look for (eg 10, 192, etc). 

All adapters are now checked for the correct adapter. A bug was discovered where, previously, only the first two were ever checked and the program would never exit

* Fixed
  * Create config file reader
  
* To do 
  * Static link libraries


### 2014-12-14
**Version 0.0.1 (Really really early build)**


Currently works by running from command line.


* Issues
  * Find out why CURL is so slow
  * Only checks if a packet is CDP or LLDP, with no distinction for filtering packets destined for phones. Causes incorrect submissions of entries to database.
  
* To do 
  * More debug info
  * Name project
  * Use TLVs instead of currently "guessing" where data is
  * Create config file reader
  * Release build to have no interface at all (automated) unless run from command line
  * Create installer to bundle everything up
  * Create Mac and Linux builds
  * Create makefile and .sln files for distribution
  * Put it all on git or sourceforge
  * FOG module
