<?php
require 'connect_db.php';
$key = $_POST['uniqueKey'];
$id =  $_POST['id'];
$who = $_POST['who'];
$name = $_POST['name'];

$db = new DBConnect();

$stmt = mysqli_stmt_init($db->getDB());
if(!mysqli_stmt_prepare($stmt,"SELECT * FROM onlineUsers WHERE userKey=? AND userID=?")){
    exit();
}else{
    mysqli_stmt_bind_param($stmt, "si", $key, $who);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_store_result($stmt);
    $resultCheck = mysqli_stmt_num_rows($stmt);
    if($resultCheck>0){
        $userFile = fopen("userFiles/gamefile".$id.".txt", "w");
        fwrite($userFile, '{"sendType":"duelRequest", "from":"'.$who.'", "senderName":"'.$name.'"}');
        fclose($userFile);
        $gameFile = fopen("gameFiles/gamefile".$id.$who.".txt", "w");
        fwrite($gameFile, '{"state":"activeRequest"}');
        fclose($gameFile);
    }else{
        exit();
    }
}
