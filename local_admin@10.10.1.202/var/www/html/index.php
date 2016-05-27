
<html>
	<body>
		<center>
			<form action="index.php" method="post">
			Asset tag
			<p>
				<input type="text" name="assetTag" autofocus="true" value="<?php echo$_POST[assetTag];?>">
			<p>
				<input type="submit" name="assetCheckButton" value="Check Availability">
	
	</body>	
</html>

<?php
	
	
	$servername = "localhost";
	$username = "root";
	$password = "L3tm31nn0w!";
	$dbname = "inventory";
	
	$conn = new mysqli($servername, $username, $password, $dbname);

	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
	if ($_POST[assetCheckButton])
	{
		$atag = mysql_escape_string($_POST[assetTag]);
	
		if ($atag != NULL)
		{
			$sql="SELECT assetTag, serialNumber, description, signedOut, userID, userName, dateOut FROM assets WHERE assetTag LIKE '%" . $atag . "%'"; 
			$result=$conn->query($sql);
			
			if ($result->num_rows > 0) 
			{
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
				
					echo "<p>Asset tag number " . $row["assetTag"]. $signoutCheck . " currently signed out";
					
					if ($row["signedOut"])
					{
						echo " to <b>" . $row["userID"] . ".</b><br>
						
						<input type='submit' name='signInButton' value='Return item'>	
						";
					}
					else
					{
						echo ". <br>
						<p>
						<input type='text' name='usID' autofocus='true'>
						<p>
						<input type='submit' name='signOutButton' value='Sign Out'>	
						";					
					}
				
				}
			} 
			else 
			{
				
			}
		}
	}
	if ($_POST[signOutButton])
	{
		
			$usID = mysql_escape_string($_POST[usID]);
			$at2 = mysql_escape_string($_POST[assetTag]);
			
		
			$sql = "UPDATE assets SET dateOut=NOW(), signedOut=1,userID=$usID WHERE assetTag=$at2";
			if ($conn->query($sql) === TRUE) 
			{
				echo "<p>Asset " . $at2 ." now signed out to " . $usID;
			}
				
	}
	if ($_POST[signInButton])
	{		
		$at2 = mysql_escape_string($_POST[assetTag]);			
		
		$sql = "UPDATE assets SET dateOut=NULL, signedOut=0,userID=NULL, userName=NULL WHERE assetTag=$at2";
		if ($conn->query($sql) === TRUE) 
		{
			echo "<p>Asset " . $at2 ." signed back in.";
		}
				
	}
	
	
	
	$conn->close();
?>
