<?php
error_reporting(E_ERROR | E_PARSE);
set_include_path ( "./classes" );
spl_autoload_register ();

$utils = new utils();
if(empty($_POST['calibration'])) {
	$allRecords = $utils->queryData("SELECT * FROM `attenuationcalibration`");
	foreach($allRecords as $record) {
		$data = $record[1];
	}
}
else {
	$mysqli = new mysqli("localhost", "jpartusch", "password", "mysql");
	$calibration = mysqli_real_escape_string($mysqli, $_POST['calibration']);
	$query = "UPDATE `attenuationcalibration` SET VALUE='$calibration' WHERE ID='1'";
	mysqli_query($mysqli, $query);
	mysqli_close($mysqli);;
}
echo $data;
?>