<?php
$myfile = fopen("testfile.txt", "w");
$txt = "John Doe\n";
fwrite($myfile, $txt);
fclose($myfile);