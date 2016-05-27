
<?php
	$servername = "localhost";
	$username = "root";
	$password = "l3tm31n";
	$dbname = "inventory";

	$astag = mysql_escape_string($_POST[assetTag]);
	$sernum = mysql_escape_string($_POST[serialNumber]);
	$desc = mysql_escape_string($_POST[description]);
	
	$test = 0;
	
	
	if ($astag == NULL)
	{
		echo "Error, asset tag is empty! ";
		$test = 1;
	}
	if ($sernum == NULL)
	{
		echo "Error, serial number is empty! ";
		$test = 1;
	}
	if ($desc == NULL)
	{
		echo "Error, description is empty! ";
		$test = 1;
	}
	
	if ($test == 0)
	{
		$conn = new mysqli($servername, $username, $password, $dbname);

		if ($conn->connect_error) 
		{
			die("Connection failed: " . $conn->connect_error);
		} 
	
		$sql = "INSERT INTO assets (assetTag, serialNumber, description)		
				VALUES ('$astag', '$sernum', '$desc')";
			
		if ($conn->query($sql) === TRUE) 
		{
			echo "New record created successfully";
		} 
		else 
		{
			echo "Error: ";
		}
	}
	
$conn->close();
?>
