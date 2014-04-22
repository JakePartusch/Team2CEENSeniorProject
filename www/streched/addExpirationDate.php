<?php
error_reporting(E_ERROR | E_PARSE);
set_include_path ( "./classes" );
spl_autoload_register ();

$utils = new utils();
if(empty($_POST["id"])) {
}
else {
	date_default_timezone_set('America/Mexico_City');
	$date = date('Y-m-d h:i:s');
	$mysqli = new mysqli("localhost", "jpartusch", "password", "mysql");
	/* check connection */
	if ($mysqli->connect_errno) 
	{
		printf("Connect failed: %s\n", $mysqli->connect_error);
		exit();
	}
	$id = mysqli_real_escape_string($mysqli, $_POST['id']);
	$endTmst = mysqli_real_escape_string($mysqli, $date);
	$query = "UPDATE `test` SET END_TMST='$endTmst' WHERE ID='$id'";
	mysqli_query($mysqli, $query);
	$query = "Select * from `test` WHERE ID='$id'";
	$allRecords = $utils->queryData($query);
	mysqli_close($mysqli);;
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
?>