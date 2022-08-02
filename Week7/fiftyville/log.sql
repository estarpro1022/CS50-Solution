-- Keep a log of any SQL queries you execute as you solve the mystery.

-- search relevant information in Humphrey Street on July 28
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND month = 7 AND day = 28;
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
 Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| 297 | 2021 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- 10:15 duck was stolen. three witnesses present and transcript mention bakery

--licence   5P2BI95
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit";
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
| 268 | 2021 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
+-----+------+-------+-----+------+--------+----------+---------------+


--search for transcripts
SELECT * FROM interviews WHERE transcript LIKE "%bakery%" AND month = 7;
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket. |
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

--first transcript useless, because we have no footage from parking lot.
--second transcript: accout records
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+


--third transcript: phone calls which are less than one minute
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60;
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 234 | (609) 555-5876 | (389) 555-5198 | 2021 | 7     | 28  | 60       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+



--leave at 7.18 10:15 people's id
SELECT DISTINCT(people.id) FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE people.license_plate IN
(SELECT bakery_security_logs.license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit");
+--------+---------+
|   id   |  name   |
+--------+---------+
| 221103 | Vanessa |
| 243696 | Barry   |
| 396669 | Iman    |
| 398010 | Sofia   |
| 449774 | Taylor  |
| 467400 | Luca    |
| 514354 | Diana   |
| 560886 | Kelsey  |
| 686048 | Bruce   |
+--------+---------+


--select phone calls less than 1 minute.
SELECT people.id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60) AND people.id IN
(SELECT DISTINCT(people.id) FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE people.license_plate IN
(SELECT bakery_security_logs.license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit"));

+--------+
|   id   |
+--------+
| 398010 |
| 449774 |
| 514354 |
| 560886 |
| 686048 |
+--------+



--airports
SELECT * FROM airports WHERE city = "Fiftyville";
+----+--------------+-----------------------------+------------+
| id | abbreviation |          full_name          |    city    |
+----+--------------+-----------------------------+------------+
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
+----+--------------+-----------------------------+------------+

SELECT b.person_id FROM bank_accounts AS b WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")
AND b.person_id IN (SELECT people.id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60) AND people.id IN
(SELECT DISTINCT(people.id) FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE people.license_plate IN
(SELECT bakery_security_logs.license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit")))

--possible people
+-----------+
| person_id |
+-----------+
| 686048    |
| 514354    |
| 449774    |
+-----------+


--search for earliest flight
SELECT * FROM flights WHERE origin_airport_id = 8 AND day = 29;
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
| 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
| 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

--find earliest flight: 8:20
--| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |


--flight information
SELECT * FROM passengers WHERE flight_id = 36;
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 7214083635      | 2A   |
| 36        | 1695452385      | 3B   |
| 36        | 5773159633      | 4A   |
| 36        | 1540955065      | 5C   |
| 36        | 8294398571      | 6C   |
| 36        | 1988161715      | 6D   |
| 36        | 9878712108      | 7A   |
| 36        | 8496433585      | 7B   |
+-----------+-----------------+------+


--passenger information
SELECT id, name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
+--------+--------+
|   id   |  name  |
+--------+--------+
| 395717 | Kenny  |
| 398010 | Sofia  |
| 449774 | Taylor |
| 467400 | Luca   |
| 560886 | Kelsey |
| 651714 | Edward |
| 686048 | Bruce  |
| 953679 | Doris  |
+--------+--------+

--suspicious
449774 Taylor
686048 Bruce


+----------------+
| account_number |
+----------------+
| 49610011       |
| 76054385       |
+----------------+
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+

--both withdraw money at Leggett Street

--However, the thief left the bakery within ten minutes after theft
--so the thief is Bruce
--accomplice's phone number is (375) 555-8161
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+
--accomplice is Robin

--destination
+----+--------------+-------------------+---------------+
| id | abbreviation |     full_name     |     city      |
+----+--------------+-------------------+---------------+
| 4  | LGA          | LaGuardia Airport | New York City |
+----+--------------+-------------------+---------------+