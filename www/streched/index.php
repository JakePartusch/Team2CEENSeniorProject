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
var chart;
var startTimestamp = getUrlParameters("startTmst", "", true);
var encodedTmst = $.param({startTmst: startTimestamp});
var getDataURL = "getData.php?" + encodedTmst;
$(function () {
        var options ={
            chart: {
				renderTo: 'container',
                type: 'spline',
				events: {
                    load: function() {
						setInterval(function() {
                            $.getJSON(getDataURL, function(data) {
								var names = [];
								var attenuationData = [];
								 $.each( data, function( key, val ) {
									names.push(key);
									attenuationData.push(val);
								 });
								 var i = 0;
								 $.each (attenuationData, function(key, val){
									chart.series[i].setData(val,true);
									i++
								 });
							});
                        }, 2000);
                    }
                }
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
                }
            },
            tooltip: {
                formatter: function() {
                        return '<b>'+ this.series.name +'</b><br/>'+
                        Highcharts.dateFormat('%e. %b', this.x) +': '+ this.y +' dbm';
                }
            },
            
            series: [{},{},{},{},{},{}]
        };
		
		$.getJSON(getDataURL, function(data) {
			var names = [];
			var attenuationData = [];
			 $.each( data, function( key, val ) {
				names.push(key);
				attenuationData.push(val);
			 });
			 var i = 0;
			 $.each (names, function(key, val){
				options.series[i].name = val;
				i++
			 });
			 var i = 0;
			 $.each (attenuationData, function(key, val){
				options.series[i].data = val;
				i++
			 });
			chart = new Highcharts.Chart(options);
		});
    });
	
function getUrlParameters(parameter, staticURL, decode){
   /*
    Function: getUrlParameters
    Description: Get the value of URL parameters either from 
                 current URL or static URL
    Author: Tirumal
    URL: www.code-tricks.com
   */
   var currLocation = (staticURL.length)? staticURL : window.location.search,
       parArr = currLocation.split("?")[1].split("&"),
       returnBool = true;
   
   for(var i = 0; i < parArr.length; i++){
        parr = parArr[i].split("=");
        if(parr[0] == parameter){
            return (decode) ? decodeURIComponent(parr[1]) : parr[1];
            returnBool = true;
        }else{
            returnBool = false;            
        }
   }
   if(!returnBool) return false;  
}	
    </script>
<script src="../../js/highcharts.js"></script>
<script src="../../js/modules/exporting.js"></script>
</head>

<body id="top">					

<div id="wrapper">	
<!-- START BLOG -->
<div class="content-wrapper clear">
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
					<div class="post-title" style="margin-bottom:2%">				
						<h2 class="title"><a href="blog-single.html">RF Monitoring System</a></h2>
					</div><!--END POST-TITLE-->
					<form action="redirect.php" method="post">
						<select name="select_receiverId">
						<?php
							/*error_reporting(E_ERROR | E_PARSE);
							set_include_path ( "./classes" );
							spl_autoload_register ();
							$utils = new Utils();
							$allRecords = $utils->queryData("SELECT * FROM `attenuationdata`");
							$receiverIdArray = $utils->getReceiverIds($allRecords);
							foreach($receiverIdArray as $receiverId)
							{
							echo $receiverId;
							echo $_GET['receiverId'];
								if($receiverId == $_GET['receiverId'])
								{
									
									echo '<option value="'.$receiverId.'" selected>Receiver '.$receiverId.'</option>';
								}
								else
								{
									echo '<option value="'.$receiverId.'">Receiver '.$receiverId.'</option>';
								}
							}*/
						?>
						</select>
						<select name= "select_range">
							<option value="today">Today</option>
							<option value="week">Week</option>
							<option value="month">Month</option>
							<option value="year">Year</option>
						</select>
						<input type="submit" />
					</form>
				</div><!--END POST-CONTENT -->
				<div id="container" style="min-width: 310px; height: 100%; margin: 0 auto"></div>
			</div><!--END POST-->
		</div><!--END INNER-CONTENT-->
</div><!--END CONTENT-WRAPPER--> 
<!-- END BLOG -->
</div><!--END WRAPPER--> 
</body>
</html>