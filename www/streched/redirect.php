<?php
$url = 'index.php?receiverId='.$_POST['select_receiverId'] . "&range=" . $_POST['select_range'];
header( "Location: $url" );
?>