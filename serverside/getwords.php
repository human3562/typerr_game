<?php
if(isset($_POST['id1']) && isset($_POST['id2']) && isset($_POST['uniqueKey'])){
//require 'connect_db.php';
$key = $_POST['uniqueKey'];
$id1 = $_POST["id1"];
$id2 = $_POST["id2"];
//$db = new DBConnect();

//$myfile = fopen("gameFiles/testfile".$id1.$id2.".txt", "r") or die("yikes");
//$file = fopen("gameFiles/testfile".$id1.$id2.".txt", "r") or die("yikes");
//$str= array();
//while (!feof($file)) {
//   $str[] = fgets($file);
//}
//fclose($file);
//echo(json_encode($str));


$myfile = fopen("gameFiles/gamefile".$id1.$id2.".txt", "r") or die("Unable to open file!");
$str = fread($myfile,filesize("gameFiles/gamefile".$id1.$id2.".txt"));
fclose($myfile);

$json = json_decode($str);
echo (json_encode($json));

//$str = mb_convert_encoding($str, "UTF-8");
//echo utf8_decode ($str);
//echo iconv("UTF-8", "ISO-8859-1//TRANSLIT", $str);
//echo (iconv("UTF-8", "CP437", $str));

}
