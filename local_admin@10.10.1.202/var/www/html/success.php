<?php

	//Log file start
	file_put_contents('./log_'.date("j.n.Y").'.txt', "=================\n", FILE_APPEND);
	

	//Server details
	$servername = "localhost";
	$username = "root";
	$password = "L3tm31nn0w!";
	$dbname = "inventory";

	//Prevent against injection exploits 
	//http://stackoverflow.com/questions/5414731/are-mysql-real-escape-string-and-mysql-escape-string-sufficient-for-app-secu
	$host = mysql_escape_string($_POST['host']);
	$ip = mysql_escape_string($_POST['ip']);
	$swPort = mysql_escape_string($_POST['swPort']);
	$swIP = mysql_escape_string($_POST['swIP']);
	$swName = mysql_escape_string($_POST['swName']);
	$swMAC = mysql_escape_string($_POST['swMAC']);
	$vlan = mysql_escape_string($_POST['vlan']);
	$mac = mysql_escape_string($_POST['mac']);
	$sp = mysql_escape_string($_POST['sp']);
	
	//This will be the test to see if a host has changed or not (or is valid)
	$testValid = 0;
	$testChanged = 0;
	
	//Use PDO in future for interoperability?
	$conn = new mysqli($servername, $username, $password, $dbname);
	
	if ($host == NULL)
	{
		echo "Error, host is empty! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, host is empty!\n", FILE_APPEND);
		$testValid = 1;
	}
	//Specific to University of Bedfordshire Computer Science department
	if ($host == "NOT-YET-AD")
	{
		echo "Error, host has not yet joined AD! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, host has not yet joined AD!\n", FILE_APPEND);
		$testValid = 1;
	}
	if ($ip == NULL)
	{
		echo "Error, ip is empty! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, ip is empty!\n", FILE_APPEND);
		$testValid = 1;
	}
	if ($swPort == NULL)
	{
		echo "Error, swPort is empty! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, swPort is empty!\n", FILE_APPEND);
		$testValid = 1;
	}
	if ($vlan == NULL)
	{
		echo "Error, vlan is empty! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, vlan is empty!\n", FILE_APPEND);
		$testValid = 1;
	}
	if ($mac == NULL)
	{
		echo "Error, mac is empty! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, mac is empty!\n", FILE_APPEND);
		$testValid = 1;
	}
	if ($swName == NULL)
	{
		echo "Error, swName is empty! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, swName is empty!\n", FILE_APPEND);
		//$testValid = 1;
	}
	if ($swMAC == NULL)
	{
		echo "Error, swMAC is empty! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, swMAC is empty!\n", FILE_APPEND);
		//$testValid = 1;
	}
	if ($swIP == NULL)
	{
		echo "Error, swIP is empty! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, swIP is empty!\n", FILE_APPEND);
		//$testValid = 1;
	}
	if ($sp == NULL)
	{
		echo "Error, sp is empty! ";
		file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Error, sp is empty!\n", FILE_APPEND);
		$testValid = 1;
	}

	if ($testValid == 0)
	{

		if ($conn->connect_error) 
		{
			die("Connection failed: " . $conn->connect_error);
			file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host."Connection failed:\n", FILE_APPEND);
		} 
	
		$sqlSelect = "SELECT * from hosts WHERE hostName = '$host'";		
		
		$result = $conn->query($sqlSelect);
		$sqlInsert = "INSERT INTO hosts (hostName, hostIP, switchPort, switchIP, switchName, switchPlatform, vlanID, hostMac, switchProto, lastChecked, lastUpdated)		
				VALUES ('$host', '$ip', '$swPort', '$swIP','$swName','$swMAC','$vlan','$mac', '$sp', NOW(), NOW())";
				
				
				
		if ($result->num_rows > 0) 
		{
			
			$row = $result->fetch_assoc();
			file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host." already exists!\n", FILE_APPEND);
			
			$changeString = "lastUpdated = NOW()";
			$changeString1 = "";
			$changeString2 = "";
			
			if ($row["hostIP"] !== $ip)
			{
				$changeString .= ",hostIP = '$ip'";
				$changeString1 .= ",historyHostIP";
				$changeString2 .= ",hostIP";
				$testChanged = 1;
			}
			if ($row["switchPort"] !== $swPort)
			{
				$changeString .= ",switchPort ='$swPort'";
				$changeString1 .= ",historySwitchPort";
				$changeString2 .= ",switchPort";
				$testChanged = 1;
			}
			if ($row["switchIP"] !== $swIP)
			{
				$changeString .= ",switchIP = '$swIP'";
				$changeString1 .= ",historySwitchIP";
				$changeString2 .= ",switchIP";
				$testChanged = 1;
			}
			if ($row["switchName"] !== $swName)
			{
				$changeString .= ",switchName = '$swName'";
				$changeString1 .= ",historySwitchName";
				$changeString2 .= ",switchName";
				$testChanged = 1;
			}
			if ($row["vlanID"] !== $vlan)
			{
				$changeString .= ",vlanID = '$vlan'";
				$changeString1 .= ",historyHostVLAN";
				$changeString2 .= ",vlanID";
				$testChanged = 1;
			}
			
			
			$sql = "UPDATE hosts SET lastChecked = NOW() WHERE hostName = '$host'";	
			if ($conn->query($sql) === TRUE) 
			{
				file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Checking for changes..\n", FILE_APPEND);
			} 	
			else 
			{
				file_put_contents('./log_'.date("j.n.Y").'.txt', date("H:i:s")." ".$host.": Error updating lastChecked.\n", FILE_APPEND);				
			}
				
			if ($testChanged == 1)
			{		
				
				//$sql = "UPDATE hosts SET lastChecked = NOW(), lastUpdated = NOW(), hostIP = '$ip', switchPort = '$swPort', switchIP = '$swIP', switchName = '$swName', switchPlatform = '$swMAC', vlanID = '$vlan', hostMac = '$mac', switchProto = '$sp' WHERE hostName = '$host'";
				//$sql = "UPDATE hosts SET lastUpdated = NOW() " . $changeString . " WHERE hostName = '$host'";		
								
				$sql = "INSERT INTO history (historyDateStart,historyHostName".$changeString1.")		
						SELECT lastUpdated,hostName".$changeString2." FROM hosts
						WHERE hostName = '$host'";
				
				if ($conn->query($sql) === TRUE) 
				{
					file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Historical entry saved.\n", FILE_APPEND);
				}
					else 
					{
						file_put_contents('./log_'.date("j.n.Y").'.txt', date("H:i:s")." ".$host.": Error saving historical entry.\n", FILE_APPEND);				
						file_put_contents('./log_'.date("j.n.Y").'.txt', " SQL string is as follows:\n".$sql."\n", FILE_APPEND);
					
					}				
				$sql = "UPDATE hosts SET ".$changeString." WHERE hostName = '$host'";	
				if ($conn->query($sql) === TRUE) 
				{
					file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Host updated!\n", FILE_APPEND);
				}
					else 
					{
						file_put_contents('./log_'.date("j.n.Y").'.txt', date("H:i:s")." ".$host.": Error updating host.\n", FILE_APPEND);				
					}
			}
			else
			{	
				file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": Host has not changed.\n", FILE_APPEND);						
			}		
			switchRecord($conn, $host, $swName, $swMAC, $swIP);		
			
		} 
		else
		if ($conn->query($sqlInsert) === TRUE) 
		{
			file_put_contents('./log_'.date("j.n.Y").'.txt',date("H:i:s")." ".$host.": New record created successfully.\n", FILE_APPEND);
			switchRecord($conn, $host, $swName, $swMAC, $swIP);
		} 
		else 
		{
			file_put_contents('./log_'.date("j.n.Y").'.txt', date("H:i:s")." ".$host.": Error: ", FILE_APPEND);
			echo "Error: ";
		}
		
		$conn->close();
	}
	function switchRecord($conn, $host,$swName,$swMAC,$swIP)
	{
		$sqlSelect = "SELECT * from switches WHERE switchID = '$swName'";
				
		$result = $conn->query($sqlSelect);

		if ($result->num_rows > 0) 
		{
			file_put_contents('./log_'.date("j.n.Y").'.txt', date("H:i:s")." ".$host.": ".$swName." already exists!\n", FILE_APPEND);
			//if ($result['swName'])
		}
		else
		{
			$sql = "INSERT INTO switches (switchID, switchPlatform, switchIP)		
					VALUES ('$swName','$swMAC','$swIP')";
			if ($conn->query($sql) === TRUE) 
			{
				file_put_contents('./log_'.date("j.n.Y").'.txt', date("H:i:s").$host.": ".$swName." created successfully.\n", FILE_APPEND);
			} 
		}
	}

?>