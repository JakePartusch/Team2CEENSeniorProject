<?php
error_reporting(E_ERROR | E_PARSE);
set_include_path ( "./classes" );
spl_autoload_register ();

$utils = new utils();
if(empty($_POST["startTmst"])) {
	$date = date('Y-m-d h:i:s');
	$mysqli = new mysqli("localhost", "jpartusch", "password", "mysql");
	/* check connection */
	if ($mysqli->connect_errno) 
	{
		printf("Connect failed: %s\n", $mysqli->connect_error);
		exit();
	}
	$name = mysqli_real_escape_string($mysqli, $_POST['name']);
	$date = mysqli_real_escape_string($mysqli, $date);
	$query = "INSERT INTO `test` (`ID`, `NAME`, `START_TMST`, `END_TMST`) VALUES (NULL, '$name', '$date', NULL)";
	mysqli_query($mysqli, $query);
	$query = "Select * from `test` WHERE NAME='$name' AND START_TMST='$date'";
	$allRecords = $utils->queryData($query);
	mysqli_close($mysqli);
	print_r($result);
	foreach($allRecords as $record)
	{
		$test = new Test();
		$test->id = $record[0];
		$test->name = $record[1];
		$test->startTmst = $record[2];
		$test->endTmst = $record[3];
	}
	echo "http://localhost/index.php?" . http_build_query($test);
}
else {
	echo "http://localhost/index.php?" . http_build_query($_POST);
}
?>