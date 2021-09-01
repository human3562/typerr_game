<?php
class DBConnect{
    //ALL this should be set to according stuff from your hosting platform
    // p.s. probably not secure

    private static $dbIP='localhost';
    private static $dbUser='root';
    private static $dbPassword = '';
    private static $dbName ='typerrdata';
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
