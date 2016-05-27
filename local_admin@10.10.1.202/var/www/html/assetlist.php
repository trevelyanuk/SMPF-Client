	<!-- 
<html>
	<body>
	-->
	
	
	<!-- 	
	dont have a comma after the last bit in the query!
	-->
	

<?php
	$servername = "localhost";
	$username = "root";
	$password = "l3tm31n";
	$dbname = "inventory";

	$conn = new mysqli($servername, $username, $password, $dbname);

	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
	

	$sql = "SELECT assetTag, serialNumber, description, signedOut, userID, userName, dateOut FROM assets";
	$result = $conn->query($sql);

	

	if ($result->num_rows > 0) 
	{	
		echo "<table><tr><th>Asset Tag</th><th>Serial Number</th><th>Description</th><th>Signed Out</th><th>Signed out to</th><th>Student ID</th><th>Date Out</th></tr>";
		while($row = $result->fetch_assoc()) 
		{
			$signedOut2 = "No";
			if ($row["signedOut"])
			{
				$signedOut2 = "Yes";
			}
			
			
			  echo "<tr><td>".
			  $row["assetTag"]."</td><td>". 
			  $row["serialNumber"]."</td><td>". 
			  $row["description"]."</td><td>". 
			  "$signedOut2"."</td><td>" . 
			  $row["userName"]."</td><td>" .
			  $row["userID"]."</td><td>".
			  $row["dateOut"]."</tr>"; 
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
