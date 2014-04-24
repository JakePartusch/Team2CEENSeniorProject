<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<meta name="viewport" content="initial-scale=1, maximum-scale=1" />
<meta name="viewport" content="width=device-width" />
<title>Team 2</title>

<link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
<link rel="stylesheet" type="text/css" href="css/style.css" media="screen" />
<link rel="stylesheet" type="text/css" href="css/blog.css" media="screen" />

</head>

<body id="top">					

<div id="wrapper">	
<!-- START BLOG -->
<div class="content-wrapper clear">
		<div id="inner-content" class="blog1">
			<div class="post">
				<div class="post-info">				
				<?php
					date_default_timezone_set('America/Mexico_City');
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
						<h2 class="title" style ="font-family: 'Oswald', sans-serif;color: #676767;font-weight: 700; text-transform: uppercase; word-spacing: 5px; padding-top:1%">Project Shield</h2>
					</div><!--END POST-TITLE-->
						
						<div class="btn-group">
							<button class="btn btn-danger btn-lg" id="submit">Stop Test</button>
							  <a class="btn dropdown-toggle" data-toggle="dropdown" href="#">
								Filter
								<span class="caret"></span>
							  </a>
							  <ul class="dropdown-menu">
									<li><a href="#" id ="day" >Day</a></li>
									<li><a href="#week" id ="week">Week</a></li>
									<li><a href="#month" id ="month">Month</a></li>
									<li><a href="#year" id ="year">Year</a></li>
									<li><a href="#all" id ="all">All-Time</a></li>
									<li><a href="" id ="clear">Clear Filter</a></li>
							  </ul>
						</div>
						<form style="padding-top:1%"class="form-inline" role="form">
						  <div class="form-group">
							<input style="width:8%"type="text" class="form-control" id="calibration" placeholder="Calibration">
							<button class="btn btn-default " id="calibrationButton">Update</button>
						  </div>
						 </form>
					
				</div><!--END POST-CONTENT -->
				<div id="container" style="min-width: 310px; height: 100%; margin: 0 auto"></div>
			</div><!--END POST-->
		</div><!--END INNER-CONTENT-->
</div><!--END CONTENT-WRAPPER--> 
<!-- END BLOG -->
</div><!--END WRAPPER--> 
</body>
<script type="text/javascript" src="js/jquery.min.js"></script>
<script type="text/javascript" src="javascript/custom.js"></script>
<script type="text/javascript" src="javascript/header.js"></script>

<script type="text/javascript" src="js/jsapi.js"></script>
 <script type="text/javascript">
var chart;
var startTimestamp = getUrlParameters("startTmst", "", true);
var endTimestamp = getUrlParameters("endTmst", "", true);
var encodedStartTmst = $.param({startTmst: startTimestamp});
var encodedEndTmst = $.param({endTmst: endTimestamp});
var getDataURL = "getData.php?" + encodedStartTmst + "&" + encodedEndTmst;
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
                    millisecond: '%m/%e %H:%M:%S',
					second: '%m/%e %H:%M:%S',
					minute: '%m/%e %H:%M:%S',
					hour: '%m/%e %H:%M',
					day: '%m/%e',
					week: '%m/%e',
					month: '%m/%e',
					year: '%m/%e'
                }
            },
            yAxis: {
                title: {
                    text: 'Attenuation (DB)'
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
$.ajax({
	  type: "GET",
	  url: "calibration.php",
	  async: true,
	  success: function (data) {
			$("#calibration").val(data);
		}
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
$("#submit").click( function() {
		var startTimestamp = getUrlParameters("id", "", true);
		var data = {id:startTimestamp};
		$.ajax({
		  type: "POST",
		  url: "addExpirationDate.php",
		  data: data,
		  async: true,
		  success: function (url) {
                window.location.assign(url);
				//alert(url);
            }
		});
		return false;
	});

$("#calibrationButton").click( function() {
		var data = {calibration:$("#calibration").val()};
		$.ajax({
		  type: "POST",
		  url: "calibration.php",
		  data: data,
		  async: true,
		});
	return false;
});
$("#day").click( function() {
		getDataURL = "getData.php?" + encodedStartTmst + "&" + encodedEndTmst + "&day=true" ;
		return true;
	});
$("#week").click( function() {
		getDataURL = "getData.php?" + encodedStartTmst + "&" + encodedEndTmst + "&week=true" ;
		return true;
	});
$("#month").click( function() {
		getDataURL = "getData.php?" + encodedStartTmst + "&" + encodedEndTmst + "&month=true" ;
		return true;
	});
$("#year").click( function() {
		getDataURL = "getData.php?" + encodedStartTmst + "&" + encodedEndTmst + "&year=true" ;
		return true;
	});
$("#all").click( function() {
		getDataURL = "getData.php?" + encodedStartTmst + "&" + encodedEndTmst + "&all=true" ;
		return true;
	});
$("#clear").click( function() {
		getDataURL = "getData.php?" + encodedStartTmst + "&" + encodedEndTmst;
		return true;
	});
    </script>
<script src="../../js/highcharts.js"></script>
<script src="../../js/modules/exporting.js"></script>
<script src="js/bootstrap.min.js"></script>
</html>