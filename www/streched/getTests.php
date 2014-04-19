<?php
error_reporting(E_ERROR | E_PARSE);
set_include_path ( "./classes" );
spl_autoload_register ();

$utils = new utils();
$allRecords = $utils->queryData("SELECT * FROM `test`");
foreach($allRecords as $record) {
	$data = array();
	foreach($allRecords as $record)
	{
		array_push($data, $record[1]);
	}
	$result->close();
}
echo json_encode(array(
    'Options' => $data);
?>