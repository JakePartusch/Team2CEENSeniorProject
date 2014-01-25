<?php
error_reporting(E_ERROR | E_PARSE);
set_include_path ( "./classes" );
spl_autoload_register ();

$utils = new Utils();
$allRecords = $utils->queryData("SELECT * FROM `attenuationdata`");
//$receiverIdArray = $utils->getReceiverIds($allRecords);
$json = new Json();
foreach($allRecords as $record)
{
	if($record->frequency == "2.4")
	{
		$temp = array($record->utc, $record->attenuation);
		//echo $record->frequency;
		$json->one[] = $temp;
	}
	else
	{
		$temp = array($record->utc, $record->attenuation);
		$json->two[] = $temp;
	}
}
echo json_encode($json);
?>