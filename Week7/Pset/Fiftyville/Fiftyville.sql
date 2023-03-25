-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Search the crime-scene-reports table
SELECT description FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28
AND street = 'Humphrey Street';

/* | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses */
SELECT * FROM interviews
WHERE transcript LIKE '%bakery%';

/* | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |*/

-- Possible license plates
SELECT * FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day =28
AND hour = 10
AND minute BETWEEN 15 AND 25;

--- account number
SELECT * FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- Name of account owner
SELECT name FROM people
WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));

-- Caller and receiver
SELECT caller, receiver FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
;

-- passengers on the ealiest flight tmr
SELECT name FROM people
WHERE passport_number IN
(SELECT passport_number FROM passengers
WHERE flight_id =
(SELECT id FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1));

-- Name of thief
-- Bank account
SELECT name FROM people
WHERE id IN (SELECT person_id FROM bank_accounts
WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))
-- Phone call
AND id IN
(SELECT id FROM people
WHERE phone_number IN
(SELECT caller FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60))
--flight
AND id IN
(SELECT id FROM people
WHERE passport_number IN
(SELECT passport_number FROM passengers
WHERE flight_id =
(SELECT id FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1)));


// Possible thief - Bruce
SELECT DISTINCT(people.name) AS thief FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw'
AND phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60
AND flights.id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1)
AND people.license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day =28 AND hour = 10 AND minute BETWEEN 15 AND 25);

-- possible cothief - Robin
SELECT name FROM people
WHERE phone_number =
(SELECT receiver FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
AND caller =
(SELECT phone_number FROM people WHERE name = 'Bruce'));


-- Destination New York City
SELECT city FROM airports
WHERE id = (
SELECT destination_airport_id FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1);

