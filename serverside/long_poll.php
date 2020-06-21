<?php

$key = $_POST['uniquekey'];
$lastUpdate = $_POST['lastupdate'];

session_write_close();
ignore_user_abort(false);
//set_time_limit(40);

try {
	// lastUpdate cookie saves the file update time which was sent to the browser
	//if (!isset($_COOKIE['lastUpdate'])) {
	//	setcookie('lastUpdate', 0);
	//	$_COOKIE['lastUpdate'] = 0;
	//}
	//$lastUpdate = $_COOKIE['lastUpdate'];
	$file = 'userFiles/testfile'.$key.'.txt';
	if (!file_exists($file)) {
		throw new Exception('file.txt Does not exist');
	}
	while (true) {
		$fileModifyTime = filemtime($file);
		if ($fileModifyTime === false) {
			throw new Exception('Could not read last modification time');
		}
		// if the last modification time of the file is greater than the last update sent to the browser... 
		if ($fileModifyTime > $lastUpdate) {
			setcookie('lastUpdate', $fileModifyTime);
			// get file contents
			$fileRead = file_get_contents($file);
			exit(json_encode([
				'status' => true,
				'time' => $fileModifyTime, 
				'content' => $fileRead
			]));
		}
		// to clear cache
		clearstatcache();
		// to sleep
		sleep(1);
	}
} catch (Exception $e) {
	exit(
		json_encode(
			array (
				'status' => false,
				'error' => $e -> getMessage()
			)
		)
	);
}