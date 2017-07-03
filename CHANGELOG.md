# Change log
## Current version - 0.0.1

* Issues
  * Find out why CURL is so slow
  * Only checks if a packet is CDP or LLDP, with no distinction for filtering packets destined for phones. Causes incorrect submissions of entries to database.
  
* To do 
  * More debug info
  * Name project
  * Use TLVs instead of currently "guessing" where data is
  * ~~Create config file reader~~
  * Release build to have no interface at all (automated) unless run from command line
  * Create installer to bundle everything up
  * Create Mac and Linux builds
  * Create makefile and .sln files for distribution
  * Put it all on git or sourceforge
  * FOG module
  * **Static link libraries**
  
  
## Change history  
### 2015-05-02
**Version 0.0.2 (Also really really early)**

Mostly just adding a configuration file. Still lots that needs doing.

A configuration file has now been added. You can specify server address, timeout, whether to use LLDP and/or CDP and what the first octet of the network address is to look for (eg 10, 192, etc). 

All adapters are now checked for the correct adapter. A bug was discovered where, previously, only the first two were ever checked and the program would never exit

* Deprecated
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
