<?php

    require 'connect_db.php';
    $mailuid = $_POST['uid'];
    $password = $_POST['pwd'];

    //echo '<br>'.$mailuid.'<br>'.$password;

    if(empty($mailuid)  || empty($password)){
        echo 'error -1';
        //header("Location: ../index.php?error=emptyfields");
        //exit();
    }else{
        $sql = "SELECT * FROM users WHERE emailUsers = ? OR uidUsers = ?";
        $db = new DBConnect();
        $stmt = mysqli_stmt_init($db->getDB());
        if(!mysqli_stmt_prepare($stmt,$sql)){
            echo 'error 3';
            //header("Location: ../index.php?error=sqlerror");
            //exit();
        }else{
            mysqli_stmt_bind_param($stmt, "ss", $mailuid, $mailuid);
            mysqli_stmt_execute($stmt);
            $result = mysqli_stmt_get_result($stmt);
            if($row = mysqli_fetch_assoc($result)){
                $pwdCheck = password_verify($password, $row['pwdUsers']);
                if($pwdCheck == false){
                    echo 'error 0 pwd';
                    //header("Location: ../index.php?error=wrongpwd");
                    //();
                }else if($pwdCheck == true){
                    //session_start();
                    //$_SESSION['userId'] = $row['idUsers'];
                    //$_SESSION['userUid'] = $row['uidUsers'];

                    //header("Location: ../index.php?login=success");
                    //exit();
                    $id = $row['idUsers'];
                    $key = md5(microtime().rand());
                    
                    $userFile = fopen("userFiles/gamefile".$id.".txt", "w");
                    fwrite($userFile, '{"sendType":"notification", "content":"login_success"}');
                    fclose($userFile);

                    $checkIfUserExists = mysqli_query($db->getDB(), "SELECT * FROM onlineUsers WHERE userID = ".$id);

                    if(mysqli_num_rows($checkIfUserExists)>0){
                        //echo 'yep';
                        mysqli_query($db->getDB(), 'UPDATE `onlineUsers` SET `userKey`="'.$key.'" WHERE `userID` = '.$id.';');
                    }else{
                        echo 'nop';
                        if(mysqli_query($db->getDB(), "INSERT INTO `onlineUsers` (`id`, `userKey`, `userID`, `userName`) VALUES (NULL, '".$key."', '".$id."', '".$row['uidUsers']."');")){
                            //echo 'what';
                        }else{
                            //echo 'nooo';
                        }
                    }


                    echo('{ "username":"'.$row['uidUsers'].'", "userId":"'.$row['idUsers'].'", "userWPM":"'.$row['avgWPM'].'", "userACC":"'.$row['avgACC'].'", "uniqueKey":"'.$key.'"}');
                }else{
                    echo 'success';
                    //header("Location: ../index.php?error=wrongpwd");
                    //exit();
                }
            }else{
                echo 'error 0';
                //header("Location: ../index.php?error=nouser");
                //exit();
            }

        }
    }
