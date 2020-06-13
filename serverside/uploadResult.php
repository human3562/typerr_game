<?php

require 'connect_db.php';
$ID = $_POST['id'];
$WPM = $_POST['wpm'];
$ACC = $_POST['acc'];

$db = new DBConnect();

$sql = "INSERT INTO `results`(`userid`, `wpm`, `acc`, `created_at`) VALUES (".$ID.",".$WPM.",".$ACC.",CURRENT_TIMESTAMP)";

mysqli_query($db->getDB(), $sql);

//mysqli_close($db);

