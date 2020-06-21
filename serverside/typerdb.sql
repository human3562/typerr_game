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

--
-- Дамп данных таблицы `onlineUsers`
--

INSERT INTO `onlineUsers` (`id`, `userKey`, `userID`, `userName`) VALUES
(2, '59cc44c48c1200e0454f9f9dfe7651ac', 4, 'skamazzz'),
(3, '15a29f9fd9d5123236132454ae405094', 5, 'SASHA'),
(5, '32b7f36be02aa8f49265f2e5a77759dc', 8, 'suck'),
(6, 'ccab0107c57d03b70ea418720426d415', 9, 'testacc'),
(7, 'f731675b8260020e4cf227bb12f6b70a', 13, 'handsomeandi'),
(8, '88b25bbc7995fb794973a93a55f25065', 14, 'Nikikita'),
(9, '920c4f156e2d9bec8848796519dde278', 15, 'Lenin');

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
-- Дамп данных таблицы `results`
--

INSERT INTO `results` (`userid`, `wpm`, `acc`, `created_at`) VALUES
(4, 57, 97, '2020-05-26 09:53:56'),
(9, 26, 91, '2020-05-26 09:54:21'),
(4, 61, 91, '2020-05-26 10:05:45'),
(5, 67, 90, '2020-05-26 10:07:11'),
(4, 54, 86, '2020-05-26 10:07:16'),
(5, 74, 97, '2020-05-26 10:23:14'),
(4, 55, 91, '2020-05-26 10:23:21'),
(5, 71, 92, '2020-05-26 10:31:24'),
(4, 51, 90, '2020-05-26 10:31:30'),
(5, 65, 92, '2020-05-26 10:32:44'),
(4, 61, 89, '2020-05-26 10:32:46'),
(5, 63, 88, '2020-05-26 10:34:41'),
(4, 56, 90, '2020-05-26 10:34:45'),
(5, 62, 88, '2020-05-26 10:43:24'),
(4, 50, 84, '2020-05-26 10:43:30'),
(5, 66, 95, '2020-05-26 10:44:28'),
(4, 56, 88, '2020-05-26 10:44:33'),
(5, 66, 93, '2020-05-26 10:45:43'),
(4, 57, 89, '2020-05-26 10:45:47'),
(5, 59, 90, '2020-05-26 10:46:42'),
(9, 66, 95, '2020-05-26 10:46:42'),
(5, 69, 100, '2020-05-26 10:47:37'),
(9, 56, 91, '2020-05-26 10:47:43'),
(5, 67, 97, '2020-05-26 10:49:29'),
(9, 58, 89, '2020-05-26 10:49:30'),
(5, 71, 97, '2020-05-26 10:50:30'),
(9, 55, 87, '2020-05-26 10:50:37'),
(4, 58, 92, '2020-05-26 11:06:01'),
(6, 37, 85, '2020-05-26 11:06:14'),
(13, 55, 88, '2020-05-26 11:11:57'),
(13, 66, 93, '2020-05-26 11:13:34'),
(6, 46, 87, '2020-05-26 11:13:41'),
(13, 56, 83, '2020-05-26 11:16:56'),
(6, 44, 86, '2020-05-26 11:17:00'),
(6, 42, 86, '2020-05-26 11:20:25'),
(13, 56, 83, '2020-05-26 11:21:45'),
(6, 44, 89, '2020-05-26 11:21:53'),
(13, 56, 85, '2020-05-26 11:24:41'),
(14, 30, 86, '2020-05-26 11:24:58'),
(6, 48, 91, '2020-05-26 11:25:17'),
(6, 48, 96, '2020-05-26 11:26:04'),
(4, 44, 75, '2020-05-26 11:26:07'),
(13, 71, 91, '2020-05-26 11:26:44'),
(4, 70, 92, '2020-05-26 11:26:45'),
(4, 61, 91, '2020-05-26 11:27:39'),
(13, 59, 83, '2020-05-26 11:27:39'),
(6, 47, 85, '2020-05-26 11:27:43'),
(14, 40, 93, '2020-05-26 11:27:50'),
(13, 62, 82, '2020-05-26 11:28:50'),
(4, 55, 88, '2020-05-26 11:28:53'),
(13, 57, 79, '2020-05-26 11:30:18'),
(4, 57, 93, '2020-05-26 16:48:11'),
(15, 40, 94, '2020-05-26 16:48:19'),
(4, 48, 90, '2020-06-09 18:46:05');

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
(1, 'human3562', '', 'human3562', 41, 90),
(2, 'stalin', '', 'sssr', 50, 90),
(3, 'aronn', '', 'aronn2014', 89, 89),
(4, 'skamazzz', 'human3562@gmail.com', '$2y$10$96gMNLZ5rGg0Xm5RSjfzMupF5mN9YX/saTs1kIB.vywb04dn9ouSi', 56, 89),
(5, 'SASHA', 'lagut.alex1@mail.ru', '$2y$10$VKpDZ2KpVVvuL3AgAdtHDeAu3RcK6Q6eSCtZ.IzFXV60EJLMrKz4G', 67, 93),
(6, 'ChlenFed', 'keks.artyom@mail.ru', '$2y$10$7uonj7LxzscR6VIcP/e.g.F.pD36R4rAR6pmDgaL4RfRUJ7IYSIEa', 45, 88),
(8, 'suck', 'suck@mail.ru', '$2y$10$vb2mXOoewQ6Zctm/rydYa.1Pt.qEpqB9fAYMRs7WjlT3RYu.cDWZS', 0, 0),
(9, 'testacc', 'human3562@gmail.com', '$2y$10$UCg1Cjki9SDm5qw8tqVWVOGHbYvwyzZq6JEDZSEBkOPzOUx3wnM8q', 52, 91),
(11, 'anothertestacc', 'test@test.test', '$2y$10$FzuAsJgmkuaoeiI6MIGCP.GlD4.K3xAxBz0RQBucidl6LynEJxzVG', 0, 0),
(12, 'thirdtestacc', 'test@test.test', '$2y$10$0lzJVrk3c/jp0tnIK/MNKugMKi83XxqFfwe5X.NK7XHhq1m/Usn.e', 0, 0),
(13, 'handsomeandi', 'lolkek@gmail.com', '$2y$10$C1xuCzq5zjstlIbFYVv7UuwRZ46WpbvvaWW/WghYovM8RihNww0aa', 60, 85),
(14, 'Nikikita', 'nikpraisethesun@gmail.com', '$2y$10$yg9ZEj.4P6vyz/pOvfNhaumSbAuaG1qEQXXHnb8wFLXJqBpf6uTE6', 35, 90),
(15, 'Lenin', 'hell@mail.com', '$2y$10$JqFOojKs0q5o5ePWTP1tKuJnjG2yf0GSarZwBC.j2y.kHOvRHTw.S', 40, 94);

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