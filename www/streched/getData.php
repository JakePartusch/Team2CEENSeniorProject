<?php
error_reporting(E_ERROR | E_PARSE);
set_include_path ( "./classes" );
spl_autoload_register ();

$utils = new utils();
if(empty($_GET[startTmst])) {
	$query = "SELECT * FROM `attenuationdata`";
}
else {
	$query = "SELECT * FROM `attenuationdata` WHERE TIMESTAMP > '$_GET[startTmst]'";
}
$allRecords = $utils->queryData($query);
$allRecords = $utils->getAttenuationObjects($allRecords);
$json = new Json();
foreach($allRecords as $record)
{
	if($record->nodeId == 1)
	{
		if($record->portId == 1)
		{
			$temp = array($record->utc, $record->attenuation);
			$json->NODE_1_PORT_1[] = $temp;
		}
		elseif($record->portId == 2)
		{
			$temp = array($record->utc, $record->attenuation);
			$json->NODE_1_PORT_2[] = $temp;
		}
		elseif($record->portId == 3)
		{
			$temp = array($record->utc, $record->attenuation);
			$json->NODE_1_PORT_3[] = $temp;
		}
	}
	else
	{
		if($record->portId == 1)
		{
			$temp = array($record->utc, $record->attenuation);
			$json->NODE_2_PORT_1[] = $temp;
		}
		elseif($record->portId == 2)
		{
			$temp = array($record->utc, $record->attenuation);
			$json->NODE_2_PORT_2[] = $temp;
		}
		elseif($record->portId == 3)
		{
			$temp = array($record->utc, $record->attenuation);
			$json->NODE_2_PORT_3[] = $temp;
		}
	}
}
echo json_encode(array(
            'Node 1: Port 1' => $json->NODE_1_PORT_1,
            'Node 1: Port 2' => $json->NODE_1_PORT_2,
            'Node 1: Port 3' => $json->NODE_1_PORT_3,
			'Node 2: Port 1' => $json->NODE_2_PORT_1,
            'Node 2: Port 2' => $json->NODE_2_PORT_2,
            'Node 2: Port 3' => $json->NODE_2_PORT_3));
?>