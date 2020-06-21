<?php
require 'connect_db.php';
$key = $_POST['uniqueKey'];
$id =  $_POST['id'];
$from = $_POST['from'];
//$name = $_POST['name'];

$db = new DBConnect();

$stmt = mysqli_stmt_init($db->getDB());
if(!mysqli_stmt_prepare($stmt,"SELECT * FROM onlineUsers WHERE userKey=? AND userID=?")){
    exit();
}else{
    mysqli_stmt_bind_param($stmt, "si", $key, $id);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_store_result($stmt);
    $resultCheck = mysqli_stmt_num_rows($stmt);
    if($resultCheck>0){
        //$userFile = fopen("userFiles/testfile".$id.".txt", "w");
        //fwrite($userFile, '{"sendType":"duelRequest", "from":"'.$who.'", "senderName":"'.$name.'"}');
        //fclose($userFile);
        //$gameFile = fopen("gameFiles/testfile".$id.$who."txt", "w");
        //fwrite($gameFile, '{"state":"activeRequest"}');
        //fclose($gameFile);
        $gameFileR = fopen('gameFiles/testfile'.$id.$from.'.txt', "r") or die("Unable to open file!");
        $jsonstr = fread($gameFileR,filesize("gameFiles/testfile".$id.$from.".txt"));
        $data = json_decode($jsonstr);
        if($data->state == "activeRequest"){
            //load game file with words.
            $gameFileW = fopen("gameFiles/testfile".$id.$from.".txt", "w") or die("YUCK");
            //$wordDB = fopen("zdb-win8.txt", "r") or die("Unable to open word database.");
            $wordDB = file("zdb-win8.txt");
            fwrite($gameFileW,"[");
            for($i = 0; $i < 10; $i++){
                $line = $wordDB[array_rand($wordDB)];
                fwrite($gameFileW, "\"");
                //$line = mb_convert_encoding($line, "");
                fwrite($gameFileW, trim($line));
                fwrite($gameFileW, "\"");
                if($i < 9){
                    fwrite($gameFileW, ", ");
                }
                else{
                    fwrite($gameFileW, "]");
                } 
            }
            
            //fclose($wordDB);
            fclose($gameFileW);
            
            $userFile = fopen("userFiles/testfile".$from.".txt", "w") or die("cant do this shit anymore");
            fwrite($userFile, '{"sendType":"requestAccepted"}');
            fclose($userFile);
            echo '{"content":"success"}';
            
        }
        fclose($gameFileR);
    }else{
        exit();
    }
}

