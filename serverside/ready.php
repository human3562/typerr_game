<?php
if(isset($_POST['from']) && isset($_POST['to'])){
    $from = $_POST['from'];
    $to = $_POST['to'];

    $userFile = fopen("userFiles/gamefile".$to.".txt", "w");
    fwrite($userFile, '{"sendType":"opponentReady"}');
    fclose($userFile);

}
