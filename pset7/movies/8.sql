-- list all the people who starred in toy story
SELECT name FROM people where id IN (SELECT person_id FROM stars WHERE movie_id = (SELECT id FROM movies WHERE title = 'Toy Story'))