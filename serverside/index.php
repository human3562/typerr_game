<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE-edge">
    <meta name="viewport" content="width = device-width" initial-scale="1">
    <title>(Typerr) Регистрация</title>

    <!-- BOOTSTRAP !-->
    <link rel="stylesheet" href="bootstrap.css">
    
    <link rel="stylesheet" href="main.css">
    
    
    <script src="https://code.jquery.com/jquery-3.4.1.min.js"
            integrity="sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo="
            crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js"
            integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo"
            crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js"
            integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6"
            crossorigin="anonymous"></script>
            

</head>

<body style="background-color: RGB(50,50,50); font-family: 'typewriterfont', arial;">
<div class="container mt-5">
    <?php
    if(isset($_GET["error"])){
        if($_GET["error"] == "usertaken"){
            echo '<div class="text-center" style="background-color: red;">Такой пользователь уже существует!</div>';
        }
        if($_GET["error"] == "passwordcheck"){
            echo '<div class="text-center" style="background-color: red;">Пароли не совпадают!</div>';
        }
    }
    ?>
    <div style="font-size: 50pt; color: white;">//Typerr <br> Регистрация </div>
    <form class="mt-2" action="signup.inc.php" method="post">
        <input type="email" class="form-control form-control-lg mb-2" name="mail" id="regmail" aria-describedby="emailHelp" placeholder="Эл. почта" required>
        <input type="text" class="form-control form-control-lg mb-2" name="uid" id="regName" placeholder="Имя пользователя" required>
        <input type="password" class="form-control form-control-lg mb-2" name="pwd" id="regpwd" placeholder="Пароль" required>
        <input type="password" class="form-control form-control-lg mb-2" name="pwd-repeat" id="regpwd-repeat" placeholder="Повторите пароль" required>
        <button type="submit" name="signup-submit" class="btn btn-lg btn-secondary">Подтвердить</button>
    </form>
</div>


</body>
</html>