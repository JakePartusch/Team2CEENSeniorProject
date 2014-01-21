<?php
error_reporting(E_ERROR | E_PARSE);
set_include_path ( "./classes" );
spl_autoload_register ();

class Utils
{


public function getReceiverIds($allRecords)
{
	$receiverIdArray;
	$i = 0;
	foreach($allRecords as $record)
	{
		if(!$this->isRecordedFrequency($record[3], $receiverIdArray))
		{
			$receiverIdArray[$i] = $record[3];
			$i++;
		}
	}
	return $receiverIdArray;
}

public function isRecordedReceiver($receiverId, $receiverIdArray)
{
	foreach($receiverIdArray as $currentReceiverid)
	{
		if($currentReceiverid == $receiverId)
		{
			return true;
		}
	}
	return false;
}
		
public function printRecords($frequency, $allRecords)
{
	foreach ($allRecords as $record)
	{
		if($record[4] == $frequency)
		{
			$this->printRecord($record);
		}
	}
}

public function printDataSeparator()
{
	echo ']';
	echo '}, {';
}

public function printDataHeader($headerName)
{
	echo "name: '". $headerName ."',";
	echo "data: [";
}

public function printFrequencyLines($frequencyArray, $allRecords)
{
	for($i = 0; $i < count($frequencyArray); $i++)
	{
		//First Entry does not need the data separator
		if($i != 0)
		{
			$this->printDataSeparator();
		}
		$this->printDataHeader($frequencyArray[$i]);
		$this->printRecords($frequencyArray[$i], $allRecords);

	}
}
					
public function getFrequencies($allRecords)
{
	$frequencyArray;
	$i = 0;
	foreach($allRecords as $record)
	{
		if(!$this->isRecordedFrequency($record[4], $frequencyArray))
		{
			$frequencyArray[$i] = $record[4];
			$i++;
		}
	}
	return $frequencyArray;
}

private function isRecordedFrequency($frequency, $frequencyArray)
{
	foreach($frequencyArray as $currentFrequency)
	{
		if($currentFrequency == $frequency)
		{
			return true;
		}
	}
	return false;
}

public function queryData($query)
{
	$mysqli = new mysqli("localhost", "jpartusch", "password", "mysql");
	/* check connection */
	if ($mysqli->connect_errno) 
	{
		printf("Connect failed: %s\n", $mysqli->connect_error);
		exit();
	}
	/* Select queries return a resultset */
	if ($result = $mysqli->query($sql = $query)) 
	{
		return $result->fetch_all();
		$result->close();
	}
}

public function printRecord ($record)
{
	$attenuationReading = new AttenuationReading();
	$attenuationReading->setDateTime($record[2]);
	$dateTime = $attenuationReading->getDateTime();
	$attentuationReading->attenuation = intVal($record[1]);
	echo '[Date.UTC('. $dateTime->year . ','. $dateTime->month . ','. $dateTime->day. ','. $dateTime->hour . ','. $dateTime->minute . ','. $dateTime->second . '),' . $attentuationReading->attenuation . '],';
}
}
?>