<?php
ini_set("allow_url_fopen",true);
?>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <title>Decibel Template</title>

    <!-- Bootstrap -->
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <script src="//d3js.org/d3.v3.min.js" charset="utf-8"></script>

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body>
 
		<?php
		// $lines = file('http://uiot.comlu.com/sensor_data.json');
		// $readings = explode(",", $lines);
		// var_dump($readings[0]);

	// 	$file = fopen("http://uiot.netai.net/sensor_data.json", "r") or die("can't open file");
// 		while (!feof($file)) {
// 			$full_line = json_decode(fgets($file),TRUE);
// 			if ( $full_line[sensorID] == 1) {
// 				$apt_file = 'apt1.json';
// 			};
// 		}
		$handle = @fopen("http://uiot.netai.net/sensor_data.json", "r");
		if (($buffer = fgets($handle, 4096)) !== false) {
			file_put_contents('apt1.json', $buffer);
		}
		fclose($handle);
		$decibel = $buffer[sensorVal];
		
		?>
		 <div class="container">
  	<div class="row">
    <h1>Noisy or Nice Dashboard!</h1>
    </div>
    <div class="row">
		<div class=".col-md-8 house">
			<svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" 
				 viewBox="0 0 640 480" xml:space="preserve">
				<style type="text/css">
					.frame{fill:#FFFFFF;stroke:#00A99D;stroke-width:4;stroke-miterlimit:10;}
					.roof{fill:#00A99D;stroke:#00A99D;stroke-width:4;stroke-miterlimit:10;}
					.quiet{fill:#FCEE21;stroke:#00A99D;stroke-width:4;stroke-miterlimit:10;}
					.moderate{fill:#FBB03B;stroke:#00A99D;stroke-width:4;stroke-miterlimit:10;}
					.loud{fill:#C1272D;stroke:#00A99D;stroke-width:4;stroke-miterlimit:10;}
					.house{width:50%;}
				</style>
				<rect x="158.1" y="126.9" class="frame" width="320.8" height="339.4"/>
				<?php if ($decibel > 0 && $decibel < 400){ ?>
				
					<rect id="apt1" x="168.5" y="135.1" class="quiet" width="93.4" height="101.6"/>	
					<?php } elseif ($decibel > 401 && $decibel < 900){ 
						echo "moderate";?>
						<rect id="apt1" x="168.5" y="135.1" class="moderate" width="93.4" height="101.6"/>	
						<?php } else {?>
							<rect id="apt1" x="168.5" y="135.1" class="loud" width="93.4" height="101.6"/>	
					<?php } 
				?>
		
				<rect id="apt2" x="272.6" y="135.1" class="quiet" width="93.4" height="101.6"/>
				<rect id="apt3" x="375.9" y="135.1" class="quiet" width="93.4" height="101.6"/>
				<rect id="apt4" x="168.9" y="244.1" class="quiet" width="93.4" height="101.6"/>
				<rect id="apt5" x="273" y="244.1" class="quiet" width="93.4" height="101.6"/>
				<rect id="apt6" x="376.3" y="244.1" class="quiet" width="93.4" height="101.6"/>
				<rect id="apt7" x="168.9" y="353.9" class="quiet" width="93.4" height="101.6"/>
				<rect id="apt8" x="273" y="353.9" class="quiet" width="93.4" height="101.6"/>
				<rect id="apt9" x="376.3" y="353.9" class="quiet" width="93.4" height="101.6"/>
				<g>
					<polyline class="roof" points="510,120 134,120 134,119.6 320,10.6 510.2,119.6"/>
				</g>
			</svg>
		</div>
		<div class=".col-md-4">
			<button type="button" onclick="loadDoc()">Display Noise Statuses</button>
		</div>
	</div>
</div>
</body>
<!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
<script>
function loadDoc() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
     document.getElementById("apt1").style.fill = xhttp.responseText;
    }
  };
  xhttp.open("GET", "ajax_info.txt", true);
  xhttp.send();
}
</script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script src="js/bootstrap.min.js"></script>
  </body>
</html>
