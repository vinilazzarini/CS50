SELECT DISTINCT(people.name) FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name != "Kevin Bacon" AND people.name IN (
SELECT people.name FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE movies.id IN (
SELECT stars.movie_id FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Kevin Bacon" AND people.birth = "1958"));

