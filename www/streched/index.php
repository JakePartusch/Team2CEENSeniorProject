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
<?php
			$mysqli = new mysqli("localhost", "jpartusch", "password", "mysql");
			$allRecords;
			/* check connection */
			if ($mysqli->connect_errno) {
				printf("Connect failed: %s\n", $mysqli->connect_error);
				exit();
			}
			/* Select queries return a resultset */
			if ($result = $mysqli->query($sql = "SELECT * FROM `attenuationdata` LIMIT 0, 30 ")) {
				$allRecords = $result->fetch_all();
				
				$result->close();
			}
			foreach ($allRecords as $record)
			{
				/*print_r($record[1]);*/
			}
				/* free result set */
		?>
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
                        Highcharts.dateFormat('%e. %b', this.x) +': '+ this.y +' m';
                }
            },
            
            series: [{
                name: '1',
                // Define the data points. All series have a dummy year
                // of 1970/71 in order to be compared on the same x axis. Note
                // that in JavaScript, months start at 0 for January, 1 for February etc.
                data: [
                    [Date.UTC(1970,  9, 27), 0   ],
                    [Date.UTC(1970, 10, 10), 0.6 ],
                    [Date.UTC(1970, 10, 18), 0.7 ],
                    [Date.UTC(1970, 11,  2), 0.8 ],
                    [Date.UTC(1970, 11,  9), 0.6 ],
                    [Date.UTC(1970, 11, 16), 0.6 ],
                    [Date.UTC(1970, 11, 28), 0.67],
                    [Date.UTC(1971,  0,  1), 0.81],
                    [Date.UTC(1971,  0,  8), 0.78],
                    [Date.UTC(1971,  0, 12), 0.98],
                    [Date.UTC(1971,  0, 27), 1.84],
                    [Date.UTC(1971,  1, 10), 1.80],
                    [Date.UTC(1971,  1, 18), 1.80],
                    [Date.UTC(1971,  1, 24), 1.92],
                    [Date.UTC(1971,  2,  4), 2.49],
                    [Date.UTC(1971,  2, 11), 2.79],
                    [Date.UTC(1971,  2, 15), 2.73],
                    [Date.UTC(1971,  2, 25), 2.61],
                    [Date.UTC(1971,  3,  2), 2.76],
                    [Date.UTC(1971,  3,  6), 2.82],
                    [Date.UTC(1971,  3, 13), 2.8 ],
                    [Date.UTC(1971,  4,  3), 2.1 ],
                    [Date.UTC(1971,  4, 26), 1.1 ],
                    [Date.UTC(1971,  5,  9), 0.25],
                    [Date.UTC(1971,  5, 12), 0   ]
                ]
            }, {
                name: '2',
                data: [
                    [Date.UTC(1970,  9, 18), 0   ],
                    [Date.UTC(1970,  9, 26), 0.2 ],
                    [Date.UTC(1970, 11,  1), 0.47],
                    [Date.UTC(1970, 11, 11), 0.55],
                    [Date.UTC(1970, 11, 25), 1.38],
                    [Date.UTC(1971,  0,  8), 1.38],
                    [Date.UTC(1971,  0, 15), 1.38],
                    [Date.UTC(1971,  1,  1), 1.38],
                    [Date.UTC(1971,  1,  8), 1.48],
                    [Date.UTC(1971,  1, 21), 1.5 ],
                    [Date.UTC(1971,  2, 12), 1.89],
                    [Date.UTC(1971,  2, 25), 2.0 ],
                    [Date.UTC(1971,  3,  4), 1.94],
                    [Date.UTC(1971,  3,  9), 1.91],
                    [Date.UTC(1971,  3, 13), 1.75],
                    [Date.UTC(1971,  3, 19), 1.6 ],
                    [Date.UTC(1971,  4, 25), 0.6 ],
                    [Date.UTC(1971,  4, 31), 0.35],
                    [Date.UTC(1971,  5,  7), 0   ]
                ]
            }, {
                name: '3',
                data: [
                    [Date.UTC(1970,  9,  9), 0   ],
                    [Date.UTC(1970,  9, 14), 0.15],
                    [Date.UTC(1970, 10, 28), 0.35],
                    [Date.UTC(1970, 11, 12), 0.46],
                    [Date.UTC(1971,  0,  1), 0.59],
                    [Date.UTC(1971,  0, 24), 0.58],
                    [Date.UTC(1971,  1,  1), 0.62],
                    [Date.UTC(1971,  1,  7), 0.65],
                    [Date.UTC(1971,  1, 23), 0.77],
                    [Date.UTC(1971,  2,  8), 0.77],
                    [Date.UTC(1971,  2, 14), 0.79],
                    [Date.UTC(1971,  2, 24), 0.86],
                    [Date.UTC(1971,  3,  4), 0.8 ],
                    [Date.UTC(1971,  3, 18), 0.94],
                    [Date.UTC(1971,  3, 24), 0.9 ],
                    [Date.UTC(1971,  4, 16), 0.39],
                    [Date.UTC(1971,  4, 21), 0   ]
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