<?php

require 'connect_db.php';
$ID = $_POST['id'];
$db = new DBConnect();
$sql = "SELECT avgWPM, avgACC FROM `users` WHERE idUsers = ".$ID;

$result = mysqli_query($db->getDB(), $sql);

if(mysqli_num_rows($result)>0){
    while($row = mysqli_fetch_array($result)){
        echo ('{"WPM":"'.$row["avgWPM"].'", "ACC":"'.$row["avgACC"].'"}');
    }
}