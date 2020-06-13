<?php
class DBConnect{
    private static $dbIP='localhost';
    private static $dbUser='id13359092_human3562';
    private static $dbPassword = '+Q<d2n0QSb54\z+R';
    private static $dbName ='id13359092_typerdb';
    private static $dbPort=3306;
    public static $db=null;

    public function __construct(){
        self::getDB();
    }
    public function __destruct(){
        if(self::$db!=null){
            mysqli_close(self::$db);
        }
    }
    public static function getDB(){
        if(self::$db===null){
            self::$db = mysqli_connect(self::$dbIP, self::$dbUser, self::$dbPassword, self::$dbName, self::$dbPort);
        }
        return self::$db;
    }
}
