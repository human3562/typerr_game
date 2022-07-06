-- phpMyAdmin SQL Dump
-- version 4.9.5
-- https://www.phpmyadmin.net/
--
-- Хост: localhost:3306
-- Время создания: Июн 13 2020 г., 11:32
-- Версия сервера: 10.3.16-MariaDB
-- Версия PHP: 7.3.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `id13359092_typerdb`
--

-- --------------------------------------------------------

--
-- Структура таблицы `onlineUsers`
--

CREATE TABLE `onlineUsers` (
  `id` int(11) NOT NULL,
  `userKey` longtext COLLATE utf8_unicode_ci NOT NULL,
  `userID` int(11) NOT NULL,
  `userName` tinytext CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


-- --------------------------------------------------------

--
-- Структура таблицы `results`
--

CREATE TABLE `results` (
  `userid` int(11) DEFAULT NULL,
  `wpm` int(4) DEFAULT NULL,
  `acc` int(3) DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


--
-- Триггеры `results`
--
DELIMITER $$
CREATE TRIGGER `updateAverages` AFTER INSERT ON `results` FOR EACH ROW BEGIN

UPDATE users 
SET users.avgWPM = (SELECT AVG(wpm) FROM results WHERE userid = NEW.userid),
users.avgACC = (SELECT AVG(acc) FROM results WHERE userid = NEW.userid)
WHERE users.idUsers = NEW.userid;

END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Структура таблицы `users`
--

CREATE TABLE `users` (
  `idUsers` int(11) NOT NULL,
  `uidUsers` tinytext NOT NULL,
  `emailUsers` tinytext NOT NULL,
  `pwdUsers` longtext NOT NULL,
  `avgWPM` int(4) NOT NULL DEFAULT 0,
  `avgACC` int(3) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `users`
--

INSERT INTO `users` (`idUsers`, `uidUsers`, `emailUsers`, `pwdUsers`, `avgWPM`, `avgACC`) VALUES
(4, 'skamazzz', 'human3562@gmail.com', '$2y$10$96gMNLZ5rGg0Xm5RSjfzMupF5mN9YX/saTs1kIB.vywb04dn9ouSi', 56, 89),
(11, 'anothertestacc', 'test@test.test', '$2y$10$FzuAsJgmkuaoeiI6MIGCP.GlD4.K3xAxBz0RQBucidl6LynEJxzVG', 0, 0),
(12, 'thirdtestacc', 'test@test.test', '$2y$10$0lzJVrk3c/jp0tnIK/MNKugMKi83XxqFfwe5X.NK7XHhq1m/Usn.e', 0, 0),

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `onlineUsers`
--
ALTER TABLE `onlineUsers`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`idUsers`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `onlineUsers`
--
ALTER TABLE `onlineUsers`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT для таблицы `users`
--
ALTER TABLE `users`
  MODIFY `idUsers` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
