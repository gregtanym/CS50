-- list the names of all people who starred in a movie in which Kevin Bacon also starred
-- list should not include kevin bacon himself
-- there may be more than one kevin bacon so u have to get the one born in 1958

SELECT name FROM people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN 
(SELECT movie_id FROM stars WHERE person_id = 
(SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958)) AND person_id NOT IN (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958)) 