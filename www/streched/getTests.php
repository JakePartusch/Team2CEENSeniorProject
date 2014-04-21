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
		$test = new Test();
		$test->name = $record[1];
		$test->startTmst = $record[2];
		$test->endTmst = $record[3];
		array_push($data, $test);
	}
}
echo json_encode(array(
    'Options' => $data));
?>