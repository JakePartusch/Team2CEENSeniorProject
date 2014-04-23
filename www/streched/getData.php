<?php
error_reporting(E_ERROR | E_PARSE);
set_include_path ( "./classes" );
spl_autoload_register ();

$utils = new utils();
date_default_timezone_set('America/Mexico_City');
$date = date('Y-m-d H:i:s');
if(empty($_GET[day]) && empty($_GET[week]) && empty($_GET[month]) && empty($_GET[year]) && empty($_GET[all])) {
	 if(empty($_GET[startTmst])) {
		$query = "SELECT * FROM `attenuationdata`";
	}
	else {
		if(empty($_GET[endTmst])) {
			$query = "SELECT * FROM `attenuationdata` WHERE TIMESTAMP > '$_GET[startTmst]'";
		}
		else {
			$query = "SELECT * FROM `attenuationdata` WHERE TIMESTAMP > '$_GET[startTmst]' AND TIMESTAMP < '$_GET[endTmst]'";
		}
	}
}
else {
	if(!empty($_GET[day])) {
		$time = strtotime("-1 day");
		$date = date('Y-m-d H:i:s', $time);
		$query = "SELECT * FROM `attenuationdata` WHERE TIMESTAMP > '$date'";
	}
	else if(!empty($_GET[week])) {
		$time = strtotime("-1 week");
		$date = date('Y-m-d H:i:s', $time);
		$query = "SELECT * FROM `attenuationdata` WHERE TIMESTAMP > '$date'";
	}
	else if(!empty($_GET[month])) {
		$time = strtotime("-1 month");
		$date = date('Y-m-d H:i:s', $time);
		$query = "SELECT * FROM `attenuationdata` WHERE TIMESTAMP > '$date'";
	}
	else if(!empty($_GET[year])) {
		$time = strtotime("-1 year");
		$date = date('Y-m-d H:i:s', $time);
		$query = "SELECT * FROM `attenuationdata` WHERE TIMESTAMP > '$date'";
	}
	else if(!empty($_GET[all])) {
		$query = "SELECT * FROM `attenuationdata`";
	}
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
			$temp = array($record->utc * 1000, $record->attenuation);
			$json->NODE_1_PORT_1[] = $temp;
		}
		elseif($record->portId == 2)
		{
			$temp = array($record->utc * 1000, $record->attenuation);
			$json->NODE_1_PORT_2[] = $temp;
		}
		elseif($record->portId == 3)
		{
			$temp = array($record->utc * 1000, $record->attenuation);
			$json->NODE_1_PORT_3[] = $temp;
		}
	}
	else
	{
		if($record->portId == 1)
		{
			$temp = array($record->utc * 1000, $record->attenuation);
			$json->NODE_2_PORT_1[] = $temp;
		}
		elseif($record->portId == 2)
		{
			$temp = array($record->utc * 1000, $record->attenuation);
			$json->NODE_2_PORT_2[] = $temp;
		}
		elseif($record->portId == 3)
		{
			$temp = array($record->utc * 1000, $record->attenuation);
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