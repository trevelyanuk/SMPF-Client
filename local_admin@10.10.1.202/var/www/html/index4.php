<html>
<head>
	<title>WebGL Demo</title>
	<link href='https://fonts.googleapis.com/css?family=Source+Sans+Pro|Open+Sans' rel='stylesheet' type='text/css'>
    <script src = "sylvester.js" type="text/javascript"></script>
    <script src = "glUtils.js" type="text/javascript"></script>
	<script src = "webGLdemo.js" type ="text/javascript"></script>
	

	<script id="shader-fs" type="x-shader/x-fragment">
	  void main(void) 
	  {
		gl_FragColor = vec4(0.95, 0.9, 1.0, 1.0);
	  }
	</script>

	<script id="shader-vs" type="x-shader/x-vertex">
	  attribute vec3 aVertexPosition;

	  uniform mat4 uMVMatrix;
	  uniform mat4 uPMatrix;
	  
	  void main(void) 
	  {
		gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
	  }
	</script>

</head>	


	<body onload="start()">
<canvas id="c" width = "700" height = "200";></canvas>


	<style>	
		div 
		{
			font-family: myFirstFont;
			font-family: 'Source Sans Pro', sans-serif;
			font-family: 'Open Sans', sans-serif;
		}
		table, td, th 
		{
			border: 0.5px solid purple;
			font-family: 'Source Sans Pro', sans-serif;
			font-size: 13;
		}
		eee
		{			
			font-family: 'Source Sans Pro', sans-serif;
			font-size: 18;
		}

		th 
		{
			background-color: 65428a;
			color: white;
			font-size: 16;
		}
	</style>
	<p>
	<eee>
		Huge tangles of patch cables stopping you finding out which wire goes to which switchport? Mapping SNMP data to host data too complex? Use Switchy McToolface to make all the hurt go away! With minimal configuration, this tool allows each host to detect which port it is connected to and report back the details of which switch is on the other end. Fun times!

	</eee>
	
	
	
	

<?php

	$servername = "localhost";
	$username = "root";
	$password = "L3tm31nn0w!";
	$dbname = "inventory";

	$conn = new mysqli($servername, $username, $password, $dbname);

	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
	

	$sql = "SELECT hostName, hostIP, hostMac, hostCreateDate, vlanID, switchPort, switchIP, switchPlatform, switchName, switchProto FROM hosts";
	$result = $conn->query($sql);

	

	if ($result->num_rows > 0) 
	{	
		echo "<table><tr><th>Hostname</th><th>IP Address</th><th>MAC</th><th>Switch IP</th><th>Switch Platform</th><th>Switch Name</th><th>Switchport ID</th><th>VLAN ID</th><th>Created On</th></tr>";
		while($row = $result->fetch_assoc()) 
		{
			  echo "<tr><td>".
			  $row["hostName"]."</td><td>". 
			  $row["hostIP"]."</td><td>". 
			  $row["hostMac"]."</td><td>". 
			  $row["switchIP"]."</td><td>" . 
			  $row["switchPlatform"]."</td><td>" .
			  $row["switchName"]."</td><td>" .
			  $row["switchPort"]."</td><td>" .
			  $row["vlanID"]."</td> <td>".
			  $row["hostCreateDate"]." via ".$row["switchProto"]." </tr>"; 
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



	-->
	</body>
</html>
