-- Keep a log of any SQL queries you execute as you solve the mystery.

--Ver a descrição do crime
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND year = 2020
AND street = "Chamberlin Street";
-- 3 testemunhas, tribunal

--Ver os depoimentos onde falam sobre tribunal
SELECT transcript FROM interviews
WHERE month = 7 AND day = 28 AND year = 2020
AND transcript LIKE "%courthouse%";

--Sei que é um homem
--Verificar quem sacou dinheiro no dia do assalto
SELECT people.name , people.phone_number, people.passport_number, people.license_plate FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (
SELECT account_number FROM atm_transactions
WHERE month = 7 AND day = 28 AND year = 2020
AND transaction_type = "withdraw"
AND atm_location LIKE "Fifer Street");

--Verificar licenças do estacionamento no dia do assalto
SELECT name FROM people
WHERE license_plate IN(
SELECT DISTINCT(license_plate) FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND year = 2020
AND license_plate IN(
SELECT people.license_plate FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (
SELECT account_number FROM atm_transactions
WHERE month = 7 AND day = 28 AND year = 2020
AND transaction_type = "withdraw"
AND atm_location LIKE "Fifer Street")));

--Verificar ligações do dia
SELECT name FROM people
WHERE phone_number IN (
SELECT caller FROM phone_calls
WHERE month = 7 AND day = 28 AND year = 2020
AND duration < 60
AND caller IN (
SELECT people.phone_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (
SELECT account_number FROM atm_transactions
WHERE month = 7 AND day = 28 AND year = 2020
AND transaction_type = "withdraw"
AND atm_location LIKE "Fifer Street")));

--ligar as duas informações
SELECT name FROM people
WHERE license_plate IN(
SELECT DISTINCT(license_plate) FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND year = 2020
AND license_plate IN(
SELECT people.license_plate FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (
SELECT account_number FROM atm_transactions
WHERE month = 7 AND day = 28 AND year = 2020
AND transaction_type = "withdraw"
AND atm_location LIKE "Fifer Street")))
AND phone_number IN (
SELECT caller FROM phone_calls
WHERE month = 7 AND day = 28 AND year = 2020
AND duration < 60
AND caller IN (
SELECT people.phone_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (
SELECT account_number FROM atm_transactions
WHERE month = 7 AND day = 28 AND year = 2020
AND transaction_type = "withdraw"
AND atm_location LIKE "Fifer Street")));

--Suspeitos Russell Ernest

SELECT id FROM airports
WHERE city LIKE "Fiftyville";

--id = 8

SELECT id FROM flights
WHERE month = 7 AND day = 29 AND year = 2020
AND origin_airport_id = 8
ORDER BY hour,minute;

-- primeiro voo 13h id = 36
SELECT name FROM people
WHERE passport_number IN(
SELECT passport_number FROM passengers
WHERE flight_id = 36);

--suspeito Ernest

SELECT destination_airport_id FROM flights
WHERE id = 36;

-- cidade final 4

SELECT city FROM airports
WHERE id = 4;