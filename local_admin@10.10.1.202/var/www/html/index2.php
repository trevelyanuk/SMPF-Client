	<!-- 
<html>
	<body>
	-->
	
	
	<!-- 	
	dont have a comma after the last bit in the query!
	-->
	

<?php
echo "Huge tangles of patch cables stopping you finding out which wire goes to which switchport? Mapping SNMP data to host data too complex? Use Switchy McToolface to make all the hurt go away! With minimal configuration, this tool allows each host to detect which port it is connected to and report back the details of which switch is on the other end. Fun times!";
	$servername = "localhost";
	$username = "root";
	$password = "L3tm31nn0w!";
	$dbname = "inventory";

	$conn = new mysqli($servername, $username, $password, $dbname);

	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
	

	$sql = "SELECT hostName, hostIP, hostMac, hostCreateDate, vlanID, switchPort, switchIP FROM hosts";
	$result = $conn->query($sql);

	

	if ($result->num_rows > 0) 
	{	
		echo "<table><tr><th>Hostname</th><th>IP Address</th><th>MAC</th><th>Switch IP</th><th>Switchport ID</th><th>VLAN ID</th><th>Created On</th></tr>";
		while($row = $result->fetch_assoc()) 
		{
			  echo "<tr><td>".
			  $row["hostName"]."</td><td>". 
			  $row["hostIP"]."</td><td>". 
			  $row["hostMac"]."</td><td>". 
			  $row["switchIP"]."</td><td>" . 
			  $row["switchPort"]."</td><td>" .
			  $row["vlanID"]."</td><td>".
			  $row["hostCreateDate"]."</tr>"; 
		}
	}
	else 
	{
		echo "0 results";
	}

$conn->close();
?>

	<!-- 	<form action="success.php" method="post">
		Hostname: <input type="text" name="host"><br>
		IP: <input type="text" name="ip"><br>
		Switchport ID: <input type="text" name="sw"><br>
		VLAN: <input type="text" name="vlan"><br>
		<input type="submit">
		</form>



	</body>
</html>
	-->
