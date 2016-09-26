<html>
    <head>
        <title>Room test</title>
        <script type="text/javascript" src="raphael.js"></script>
        <script type="text/javascript" src="test_script.js"></script>
        <style type="text/css">
            #canvas_container {
                width: 500px;
                border: 1px solid #aaa;
            }
        </style>
    </head>
    <body>
        <div id="canvas_container"></div>
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
	
	$getHosts = "SELECT * from hosts WHERE Room = 'E106'";
	
	$resulties = array();
	
	if ($result = $conn->query($getHosts))
	{
		while ($row = $result->fetch_array(MYSQL_ASSOC))
		{
			$resulties[] = $row;
		}
	 if ($json = json_encode($resulties));
	
		{
			echo $json;
		}
	}
	
	$conn->close();
?>
	