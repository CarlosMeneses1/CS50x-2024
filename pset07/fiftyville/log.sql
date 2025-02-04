-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene descripstions of the whole day
SELECT *
  FROM crime_scene_reports
 WHERE month = 7
   AND day = 28;

-- Find the the transcript of the interview of the three witnesses
SELECT *
  FROM interviews
 WHERE month = 7
   AND day = 28;

-- Clue #1 | Witness #1: Ruth
-- Find parking lot logs
SELECT license_plate
  FROM bakery_security_logs
 WHERE month = 7
   AND day = 28
   AND hour = 10
   AND minute >= 15 AND minute <= 25
   AND activity = 'exit';

-- Clue #2 | Witness #2: Eugene
-- Find account numbers
SELECT account_number
  FROM atm_transactions
 WHERE month = 7
   AND day = 28
   AND atm_location = 'Leggett Street'
   AND transaction_type = 'withdraw';

-- List of suspects according to 'account numbers' AND 'license plate'
SELECT *
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
 WHERE bank_accounts.account_number IN (
       SELECT account_number
         FROM atm_transactions
        WHERE month = 7
          AND day = 28
          AND atm_location = 'Leggett Street'
          AND transaction_type = 'withdraw')
   AND people.license_plate IN (
       SELECT license_plate
         FROM bakery_security_logs
        WHERE month = 7
          AND day = 28
          AND hour = 10
          AND minute >= 15 AND minute <= 25
          AND activity = 'exit');

-- Clue #3 | Witness #3: Raymond
-- Find calls logs (caller = thief, receiver = accomplice)
SELECT caller, receiver
  FROM phone_calls
 WHERE month = 7
   AND day = 28
   AND duration <= 60;

-- List of suspects according to 'account numbers' AND 'license plate' AND 'phone number'
SELECT *
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
 WHERE bank_accounts.account_number IN (
       SELECT account_number
         FROM atm_transactions
        WHERE month = 7
          AND day = 28
          AND atm_location = 'Leggett Street'
          AND transaction_type = 'withdraw')
   AND people.license_plate IN (
       SELECT license_plate
         FROM bakery_security_logs
        WHERE month = 7
          AND day = 28
          AND hour = 10
          AND minute >= 15 AND minute <= 25
          AND activity = 'exit')
   AND people.phone_number IN (
       SELECT caller
         FROM phone_calls
        WHERE month = 7
          AND day = 28
          AND duration <= 60);

-- Find the earliest flight on the 29th
SELECT *
  FROM flights
 WHERE month = 7
   AND day = 29
   AND hour = (
       SELECT MIN(hour)
         FROM flights
        WHERE month = 7
          AND day = 29);

-- Find the passport number of the passengers of the earliest flight on the 29th
SELECT passaport_number
  FROM passenger
  JOIN flights
    ON passengers.flight_id = flights.id
 WHERE month = 7
   AND day = 29
   AND hour = (
       SELECT MIN(hour)
         FROM flights
        WHERE month = 7
          AND day = 29);

-- List of suspects according to 'account numbers' AND 'license plate' AND 'phone number' AND 'passport number'
SELECT *
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
 WHERE bank_accounts.account_number IN (
       SELECT account_number
         FROM atm_transactions
        WHERE month = 7
          AND day = 28
          AND atm_location = 'Leggett Street'
          AND transaction_type = 'withdraw')
   AND people.license_plate IN (
       SELECT license_plate
         FROM bakery_security_logs
        WHERE month = 7
          AND day = 28
          AND hour = 10
          AND minute >= 15 AND minute <= 25
          AND activity = 'exit')
   AND people.phone_number IN (
       SELECT caller
         FROM phone_calls
        WHERE month = 7
          AND day = 28
          AND duration <= 60)
    AND people.passport_number IN (
        SELECT passport_number
          FROM passengers
          JOIN flights
            ON passengers.flight_id = flights.id
         WHERE month = 7
           AND day = 29
           AND hour = (
               SELECT MIN(hour)
                 FROM flights
                WHERE month = 7
                  AND day = 29));

-- Find the thief's destination
SELECT city
  FROM airports
  JOIN flights
    ON airports.id = flights.destination_airport_id
 WHERE month = 7
   AND day = 29
   AND hour = (
       SELECT MIN(hour)
         FROM flights
        WHERE month = 7
          AND day = 29);

-- Find the name of the accomplice from the phone call
SELECT *
  FROM people
 WHERE phone_number = (
       SELECT receiver
         FROM phone_calls
        WHERE month = 7
          AND day = 28
          AND caller = (
              SELECT phone_number
                FROM people
               WHERE name = 'Bruce'));
