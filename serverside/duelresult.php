<?php
if(isset($_POST['from']) && isset($_POST['to'])){
    $from = $_POST['from'];
    $to = $_POST['to'];
    $time = $_POST['time'];
    $WPM = $_POST['wpm'];
    $ACC = $_POST['acc'];
    $score = $_POST['score'];
    
    $userFile = fopen("userFiles/testfile".$to.".txt", "w");
    fwrite($userFile, '{"sendType":"opponentResult", "time":"'.$time.'", "WPM":"'.$WPM.'", "ACC":"'.$ACC.'", "score":"'.$score.'"}');
    fclose($userFile);
    echo '{"content":"success"}';
}