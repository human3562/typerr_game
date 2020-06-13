<?php

$key = $_POST['uniquekey'];

$file_pointer = realpath("userfiles/testfile".$key.".txt");  

echo $file_pointer;

if (!unlink($file_pointer)) {  
    echo ("$file_pointer cannot be deleted due to an error");  
}  
else {  
    echo ("$file_pointer has been deleted");  
}  