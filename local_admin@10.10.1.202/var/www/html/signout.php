<?php
	$atag = mysql_escape_string($_POST[assetTag]);
	
	$servername = "localhost";
	$username = "root";
	$password = "l3tm31n";
	$dbname = "inventory";
	
	$conn = new mysqli($servername, $username, $password, $dbname);

	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
	
	$sql="SELECT assetTag, serialNumber, description, signedOut, userID, userName, dateOut FROM assets WHERE assetTag LIKE '%" . $atag . "%'"; 

	$result=$conn->query($sql);
	if ($result->num_rows > 0) 
	{

    // output data of each row
		while($row = $result->fetch_assoc()) 
		{
			
			if ($row["signedOut"])
			{
				$signoutCheck = " is";
			}
			else
			{
				$signoutCheck = " is not";
			}
		
			echo "Asset tag number " . $row["assetTag"]. $signoutCheck . " signed out";
			
			if ($row["signedOut"])
			{
			echo " to " . $row["userName"] . $atag .  ". <br>";
			}
			else
			{
				echo ". <br>";			
			}
		
		}
	} 
	else 
	{
		echo "0 results";
	}
	
	
	
	$conn->close();
?>
