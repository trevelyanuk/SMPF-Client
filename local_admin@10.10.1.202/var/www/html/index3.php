	<!-- 
<html>
	<body>
	-->
	
	
	<!-- 	
	dont have a comma after the last bit in the query!
	-->
	
	
<html>
	<body>

	<link href='https://fonts.googleapis.com/css?family=Source+Sans+Pro|Open+Sans' rel='stylesheet' type='text/css'>
	
<canvas id="c"
		width = "700"
		height = "100";>
</canvas>

<script>
	var gl;
	var canvas = document.getElementById("c");
  
  
	gl = initGL(canvas);
	if (gl)
	{
		gl.clearColor(0,0,0, 1);
		gl.enable(gl.DEPTH_TEST);
		gl.depthFunc(gl.LEQUAL);
		gl.clear(gl.COLOR_BUFFER_BIT|gl.DEPTH_BUFFER_BIT);		
	}	
	else
	{
		
	}
	
	function main()
	{
		
	}
	function initGL(can)
	{
		can.getContext("webgl") || can.getContext("experimental-webgl");	
	}
	
	function initShaders()
	{		
		var fragmentShader = getShader(gl, "shader-fs");
		var vertexShader = getShader(gl, "shader-vs");
			
		//New shaderProgram
		shaderProgram = gl.createProgram();
		
		//attach two shaders for Vertex/Fragment
		gl.attachShader(shaderProgram, vertexShader);
		gl.attachShader(shaderProgram, fragmentShader);
		
		//link those attached shaders
		gl.linkProgram(shaderProgram);	
		
		if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) 
		{
			alert("Unable to initialize the shader program.");
		}
		
		//use this program (we could have lots of programs)
		gl.useProgram(shaderProgram);
  
  
		//No idea
		 vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
		 gl.enableVertexAttribArray(vertexPositionAttribute);
  
	}
	function getShader(gl, id)
	{
		var shaderScript;
		var theSource;
		var currentChild;
		var shader;
		
		shaderScript = document.getElementById(id);
		if (!shaderScript)
		{
			return null;
		}
		
		theSource = "";
		currentChild = shaderScript.firstChild;
		
		while(currentChild) 
		{
			if (currentChild.nodeType == currentChild.TEXT_NODE) 
			{
			  theSource += currentChild.textContent;
			}
			
			currentChild = currentChild.nextSibling;
		}
		if (shaderScript.type == "x-shader/x-fragment") 
		{
			shader = gl.createShader(gl.FRAGMENT_SHADER);
		} 
		else 
			if (shaderScript.type == "x-shader/x-vertex") 
			{
				shader = gl.createShader(gl.VERTEX_SHADER);
			} 
			else 
			{
				// Unknown shader type
				return null;
			}
		
		gl.shaderSource(shader, theSource);
		
		// Compile the shader program
		gl.compileShader(shader);      
		
		// See if it compiled successfully
		if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) 
		{  
			alert("An error occurred compiling the shaders: " + gl.getShaderInfoLog(shader)); 
			return null;  
		}    
		
		return shader;
	}
</script>


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
	
	<eee>
		LSFC Switch Thing v0.1
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
