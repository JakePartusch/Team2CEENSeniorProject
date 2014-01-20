<?php
class AttenuationReading {

public $attenuation;
private $dateTime;

	public function setDateTime($timestamp)
	{
		$dateTime = new DateTime();
		$split = explode("-", $timestamp);
		$dateTime->year = intVal($split[0]);
		$dateTime->month = intVal($split[1]);
		$split = explode(" ", $split[2]);
		$dateTime->day = intVal($split[0]);
		$split = explode(":", $split[1]);
		$dateTime->hour = intVal($split[0]);
		$dateTime->minute = intVal($split[1]);
		$dateTime->second = intVal($split[2]);
		$this->dateTime = $dateTime;
	}
	public function getDateTime()
	{
		return $this->dateTime;
	}

}
?>