
1
SELECT title FROM movies
WHERE year = 2008;

2
SELECT birth FROM people
WHERE name = 'Emma Stone';

3
SELECT title FROM movies
WHERE year >=  2018
ORDER BY title;

4
SELECT COUNT(*) FROM ratings
WHERE rating = 10;

5
SELECT title, year FROM movies
WHERE title LIKE 'Harry Potter%'
ORDER BY year;

6
SELECT AVG(rating) FROM ratings
WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);

7
SELECT title, rating
FROM movies, ratings
WHERE movies.id = ratings.movie_id
AND year = 2010
ORDER BY rating DESC, title

8
SELECT name FROM  people
WHERE id IN (SELECT person_id FROM stars WHERE movie_id = (SELECT id FROM movies WHERE title = 'Toy Story'));

9
SELECT name FROM people
WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004))
ORDER BY birth

10
SELECT DISTINCT(name) FROM people
WHERE id IN (SELECT person_id FROM directors WHERE movie_id IN (SELECT movie_id FROM ratings WHERE rating >= 9.0));

11
SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;

12
SELECT title FROM movies
WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Johnny Depp'))
AND id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Helena Bonham Carter'))
ORDER BY year;

13
SELECT name FROM people
WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958)))
AND id != (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958);
