<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<meta name="viewport" content="initial-scale=1, maximum-scale=1" />
<meta name="viewport" content="width=device-width" />
<title>Team 2</title>

<link rel="stylesheet" type="text/css" href="css/style.css" media="screen" />
<link rel="stylesheet" type="text/css" href="css/blog.css" media="screen" />
<link href='http://fonts.googleapis.com/css?family=Oswald:400,700,300' rel='stylesheet' type='text/css' />

<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.4.4/jquery.min.js"></script>
<script type="text/javascript" src="javascript/custom.js"></script>
<script type="text/javascript" src="javascript/header.js"></script>
	
<script type="text/javascript" src="https://www.google.com/jsapi"></script>
    <script type="text/javascript">

$(function () {
        $('#container').highcharts({
            chart: {
                type: 'spline'
            },
            title: {
                text: 'Attentuation Data of the Concrete'
            },
            subtitle: {
                text: ''
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: { // don't display the dummy year
                    month: '%e. %b',
                    year: '%b'
                }
            },
            yAxis: {
                title: {
                    text: 'Attenuation (dbm)'
                },
                min: 0
            },
            tooltip: {
                formatter: function() {
                        return '<b>'+ this.series.name +'</b><br/>'+
                        Highcharts.dateFormat('%e. %b', this.x) +': '+ this.y +' dbm';
                }
            },
            
            series: [{
               
				<?php
					//Removes Warnings and Imports necessary object classes
					error_reporting(E_ERROR | E_PARSE);
					set_include_path ( "./classes" );
					spl_autoload_register ();

					//TODO: make receiverId dynamic
					$allRecords = queryData("SELECT * FROM `attenuationdata` where receiverId = '1'");
					$frequencyArray = getFrequencies($allRecords);
					printFrequencyLines($frequencyArray, $allRecords);
							
					function printRecords($frequency, $allRecords)
					{
						foreach ($allRecords as $record)
						{
							if($record[4] == $frequency)
							{
								printRecord($record);
							}
						}
					}
					
					function printDataSeparator()
					{
						echo ']';
						echo '}, {';
					}
					
					function printDataHeader($headerName)
					{
						echo "name: '". $headerName ."',";
						echo "data: [";
					}
					
					function printFrequencyLines($frequencyArray, $allRecords)
					{
						for($i = 0; $i < count($frequencyArray); $i++)
						{
							//First Entry does not need the data separator
							if($i != 0)
							{
								printDataSeparator();
							}
							printDataHeader($frequencyArray[$i]);
							printRecords($frequencyArray[$i], $allRecords);

						}
					}
										
					function getFrequencies($allRecords)
					{
						$frequencyArray;
						$i = 0;
						foreach($allRecords as $record)
						{
							if(!isRecordedFrequency($record[4], $frequencyArray))
							{
								$frequencyArray[$i] = $record[4];
								$i++;
							}
						}
						return $frequencyArray;
					}
					function isRecordedFrequency($frequency, $frequencyArray)
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
					function queryData($query)
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
					
					function printRecord ($record)
					{
						$attenuationReading = new AttenuationReading();
						$attenuationReading->setDateTime($record[2]);
						$dateTime = $attenuationReading->getDateTime();
						$attentuationReading->attenuation = intVal($record[1]);
						echo '[Date.UTC('. $dateTime->year . ','. $dateTime->month . ','. $dateTime->day. ','. $dateTime->hour . ','. $dateTime->minute . ','. $dateTime->second . '),' . $attentuationReading->attenuation . '],';
					}
				?>
				]
			}]	
        });
    });
    </script>
<script src="../../js/highcharts.js"></script>
<script src="../../js/modules/exporting.js"></script>
</head>

<body id="top">					
<!-- START HEADER -->
<div id="header-wrapper">
	<div class="header clear">
		<div id="logo">	
			<a href="index.html"><img src="images/logo.jpg" alt="" /></a>		
		</div><!--END LOGO-->
		<div id="primary-menu">
			<ul class="menu">
				<li><a href="index.html">Home</a>		
					<ul>
						<li><a href="index.html">Home</a></li>
					</ul>
			   </li>
			</ul>
		</div><!--END PRIMARY MENU-->
	</div><!--END HEADER-->	
</div><!--END HEADER-WRAPPER-->		
<!-- END HEADER -->
<div id="wrapper">	
<!-- START BLOG -->
<div class="content-wrapper clear">
	<div class="section-title">
		<h1 class="title">Radio Frequency Data</h1>				
	</div><!--END SECTION TITLE-->
		<div id="inner-content" class="blog1">
			<div class="post">
				<div class="post-info">				
				<?php
					echo '<div class="date"><span class="month">';
					echo date('M');
					echo '</span><span class="day">';
					echo date('d');
					echo '</span><span class="month">';
					echo date('Y');
					echo '</span></div>';	
				?>
				</div><!--END POST-INFO-->		
				<div class="post-content">	
					<div class="post-title">				
						<h2 class="title"><a href="blog-single.html">Current Data</a></h2>
					</div><!--END POST-TITLE-->
					<div class="post-meta">				
						<ul>
							<li><span>Posted by</span> <a href="#">RF Monitoring System</a></li>
						</ul>
					</div><!--END POST-META-->	
								
					<div id="container" style="min-width: 310px; height: 400px; margin: 0 auto"></div>
				</div><!--END POST-CONTENT -->
			</div><!--END POST-->
		</div><!--END INNER-CONTENT-->
</div><!--END CONTENT-WRAPPER--> 
<!-- END BLOG -->
</div><!--END WRAPPER--> 
<!-- START FOOTER -->
<div id="footer">
	<div id="footer-content">		
		<div id="footer-bottom" class="clear">			
			<div class="one-half">
				<p>Team 2: Jake, Tyler, Kossivi</p>
			</div><!--END ONE-HALF-->	
		</div><!--END FOOTER-BOTTOM-->	
	</div><!--END FOOTER-CONTENT-->	
</div><!--END FOOTER-->

</body>
</html>