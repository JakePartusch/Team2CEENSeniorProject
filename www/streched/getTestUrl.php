<?php
if(empty($_POST)){
	echo "insert";
}
else {
	echo "http://localhost/index.php?" . http_build_query($_POST);
}
?>