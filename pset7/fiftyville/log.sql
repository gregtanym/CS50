-- Keep a log of any SQL queries you execute as you solve the mystery.

-- crime happened on 28/07/2020
-- on Chamberlin Street

-- its probably smart to look at the crime scene report first, maybe there are more clues
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Chamberlin Street';
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the courthouse.

select * from interviews where year = 2020 and month = 7 and day = 28;
-- Eugene recognised the thief
-- thief was seen withdrawing money on fifer street before 1015 (atm_transactions)
-- between 1015 and 1025, the thief got into a car at the courthouse and drove off (courthouse_security_logs)
-- called someone for less than a minute , take earliest flight out, accomplice to produce flight tix (flights, phone_calls + passengers, airport)

select account_number from atm_transactions where year = 2020 and month = 7 and day = 28 and atm_location = 'Fifer Street' and transaction_type = 'withdraw';
-- a bit inconclusive coz there were 8 withdrawals on that day, no indication of timing
-- account number could prove useful to check if it was used in any other escape means
-- 28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199

select license_plate from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25;
-- there were 8 exits, tho i would exclude the first 4 coz it is unlikely to happen that fast
-- license plate are:
-- 5P2BI95 (1016), 94KL13X or 6P58WS2 (1018), 4328GD8 (1019), G412CB7 (1020), L93JTIZ (1021), 322W7JE or 0NTHK55 (1023)

select caller, receiver from phone_calls where year = 2020 and month = 7 and day = 28 and duration <= 60;
-- thief is the caller, accomplice is the receiver

select passport_number from passengers where flight_id IN
(select id from flights where origin_airport_id IN
(select id from airports where city = 'Fiftyville')
and year = 2020
and month = 7
and day = 29
order by hour, minute
limit 1);
-- potential passport numbers for both the thief and the accomplice:
--

select id, name from people where phone_number in
(select caller from phone_calls where year = 2020 and month = 7 and day = 28 and duration <= 60)
and passport_number in
(select passport_number from passengers where flight_id IN
(select id from flights where origin_airport_id IN
(select id from airports where city = 'Fiftyville')
and year = 2020
and month = 7
and day = 29
order by hour, minute
limit 1))
and license_plate in
(select license_plate from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25);
--this query will check through the people database and see if there is anyone who has the passport number, phone number and license plate of the shortlisted data from the other evidence
-- i am left with 3 suspects (roger, evelyn and ernest)
-- but i have yet to check their bank accounts to see who withdrew money on 28/07/20

select id, name from people where id IN
(select person_id from bank_accounts where account_number IN
(select account_number from atm_transactions where year = 2020 and month = 7 and day = 28 and atm_location = 'Fifer Street' and transaction_type = 'withdraw'));
-- from here its pretty obvs that there is only one name that overlaps


--FINAL QUERY TO FIND THIEF
select id, name from people where phone_number in
(select caller from phone_calls where year = 2020 and month = 7 and day = 28 and duration <= 60)
and passport_number in
(select passport_number from passengers where flight_id IN
(select id from flights where origin_airport_id IN
(select id from airports where city = 'Fiftyville')
and year = 2020
and month = 7
and day = 29
order by hour, minute
limit 1))
and license_plate in
(select license_plate from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25)
AND id IN
(select person_id from bank_accounts where account_number IN
(select account_number from atm_transactions where year = 2020 and month = 7 and day = 28 and atm_location = 'Fifer Street' and transaction_type = 'withdraw'));
-- the thief is ernest (686048)

-- it should be easier to find the destination first
select city from airports where id IN
(select destination_airport_id from flights where origin_airport_id IN
(select id from airports where city = 'Fiftyville')
and year = 2020
and month = 7
and day = 29
order by hour, minute
limit 1);
-- this is the first flight on 29/07 which the thieves took
-- they went to LONDON

--i should be focusing on ernest number and when he called that someone during the theft
select phone_number from people where name = 'Ernest';
-- got his number, now i just need to find out EXACTLY who he was calling

select receiver from phone_calls where caller =
(select phone_number from people where name = 'Ernest')
and year = 2020 and month = 7 and day = 28 and duration <= 60;
-- got the persons number

select name from people where phone_number =
(select receiver from phone_calls where caller =
(select phone_number from people where name = 'Ernest')
and year = 2020 and month = 7 and day = 28 and duration <= 60);
-- the accomplice name is berthold










-- method of finding accomplice that didnt work:


-- to find the accomplice, the only lead is his phone number which should be enough
select receiver from phone_calls where year = 2020 and month = 7 and day = 28 and duration <= 60;
-- one of these numbers is the accomplice number

select passport_number from passengers where flight_id =
(select id from flights where origin_airport_id IN
(select id from airports where city = 'Fiftyville')
and year = 2020
and month = 7
and day = 29
order by hour, minute
limit 1);
-- one of these is the accomplice passport number

select name from people where phone_number IN
(select receiver from phone_calls where year = 2020 and month = 7 and day = 28 and duration <= 60)
and passport_number IN
(select passport_number from passengers where flight_id =
(select id from flights where origin_airport_id IN
(select id from airports where city = 'Fiftyville')
and year = 2020
and month = 7
and day = 29
order by hour, minute
limit 1))
and license_plate IN
(select license_plate from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25);
-- this is assuming that her license plate was seen at the crime scene





