<?php
if(isset($_POST['signup-submit'])){
    require 'connect_db.php';

    $username =       $_POST['uid'];
    $email =          $_POST['mail'];
    $password =       $_POST['pwd'];
    $passwordRepeat = $_POST['pwd-repeat'];

    if(empty($username) || empty($email) || empty($password) || empty($passwordRepeat)){
        header("Location: ../index.php?error=emptyfields&uid=".$username."&mail=".$email);
        exit();
    } else if(!filter_var($email, FILTER_VALIDATE_EMAIL) && !preg_match('/^([а-яА-ЯЁёa-zA-Z0-9_]+)$/u', $username)) {
        header("Location: ../index.php?error=invalidmailuid");
        exit();
    } else if(!filter_var($email, FILTER_VALIDATE_EMAIL)){
        header("Location: ../index.php?error=invalidmail&uid=".$username);
        exit();
    } else if(!preg_match('/^([а-яА-ЯЁёa-zA-Z0-9_]+)$/u', $username)){
        header("Location: ../index.php?error=invaliduid&mail=".$email);
        exit();
    } else if($password !== $passwordRepeat){
        header("Location: ../index.php?error=passwordcheck&uid=".$username."&mail=".$email);
        exit();
    } else {
        //$sql = "SELECT uidUsers FROM users WHERE uidUsers=?";
        $db = new DBConnect();
        $conn = $db->getDB();
        $stmt = mysqli_stmt_init($conn);
        if(!mysqli_stmt_prepare($stmt,"SELECT uidUsers FROM users WHERE uidUsers=?")){
            header("Location: ../index.php?error=sqlerror");
            //echo(mysqli_stmt_error($stmt));
            exit();
        } else {
            mysqli_stmt_bind_param($stmt, "s", $username);
            mysqli_stmt_execute($stmt);
            mysqli_stmt_store_result($stmt);
            $resultCheck = mysqli_stmt_num_rows($stmt);
            if($resultCheck > 0){
                header("Location: ../index.php?error=usertaken");
                exit();
            } else{

                $sql = "INSERT INTO users (uidUsers, emailUsers, pwdUsers) VALUES (?, ?, ?)";
                $stmt = mysqli_stmt_init($conn);
                if(!mysqli_stmt_prepare($stmt, $sql)) {
                    header("Location: ../index.php?error=sqlerror");
                    exit();
                } else{
                    $hashedPwd = password_hash($password, PASSWORD_DEFAULT);

                    mysqli_stmt_bind_param($stmt, "sss", $username,  $email, $hashedPwd);
                    mysqli_stmt_execute($stmt);

                    //echo '<p>Вы успешно зарегистрировались!</p>';
                    require 'success.html';
                    //header("Location: ../index.php?signup=success");
                    //exit();
                }

            }
        }

    }
    mysqli_stmt_close($stmt);
    //mysqli_close($conn);

} else{
    header("Location: ../index.php");
    exit();
}
