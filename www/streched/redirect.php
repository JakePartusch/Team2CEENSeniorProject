<?php
$url = 'index.php?receiverId='.$_POST['select_receiverId'];
header( "Location: $url" );
?>