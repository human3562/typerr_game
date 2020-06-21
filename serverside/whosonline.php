<?php
require 'connect_db.php';
$db = new DBConnect();

$idArray = array();

$query = mysqli_query($db->getDB(), 'SELECT * FROM onlineUsers');
if(mysqli_num_rows($query) > 0){
    while($row = mysqli_fetch_assoc($query)){
        $id = $row['userID']; $name = $row['userName'];
        array_push($idArray, array($id, $name));
    }
}

echo(json_encode($idArray));
