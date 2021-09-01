<?php
$myfile = fopen("gamefile.txt", "w");
$txt = "John Doe\n";
fwrite($myfile, $txt);
fclose($myfile);
