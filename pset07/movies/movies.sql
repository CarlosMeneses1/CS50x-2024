-- 1. write a SQL query to list the titles of all movies released in 2008.
SELECT title
  FROM movies
 WHERE year = 2008;

-- 2. write a SQL query to determine the birth year of Emma Stone
SELECT birth
  FROM people
 WHERE name = 'Emma Stone';

-- 3. write a SQL query to list the titles of all movies with a release date on or after 2018, in alphabetical order.
SELECT title
  FROM movies
 WHERE year >= 2018
 ORDER BY title;

-- 4. write a SQL query to determine the number of movies with an IMDb rating of 10.0
SELECT COUNT(title)
  FROM movies
  JOIN ratings
    ON movies.id = ratings.movie_id
 WHERE rating = 10.0;

-- 5. write a SQL query to list the titles and release years of all Harry Potter movies, in chronological order
SELECT title, year
  FROM movies
 WHERE title LIKE 'Harry Potter%'
 ORDER BY year;

-- 6. write a SQL query to determine the average rating of all movies released in 2012
SELECT AVG(rating)
  FROM ratings
  JOIN movies
    ON ratings.movie_id = movies.id
 WHERE movies.year = 2012;

-- 7. write a SQL query to list all movies released in 2010 and their ratings,
-- in descending order by rating. For movies with the same rating, order them alphabetically by title.
SELECT title, rating
  FROM movies
  JOIN ratings
    ON movies.id = ratings.movie_id
 WHERE movies.year = 2010
 ORDER BY rating DESC, title ASC;

-- 8. write a SQL query to list the names of all people who starred in Toy Story
SELECT name
  FROM people
 WHERE id IN (
       SELECT person_id
         FROM stars
        WHERE movie_id = (
              SELECT id
                FROM movies
               WHERE title = 'Toy Story'));

-- 9. write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year
SELECT name
  FROM people
 WHERE id IN (
       SELECT person_id
         FROM stars
        WHERE movie_id IN (
              SELECT id
                FROM movies
               WHERE year = 2004))
 ORDER BY birth ASC;

-- 10. write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0
SELECT name
  FROM people
 WHERE id IN (
       SELECT person_id
         FROM directors
        WHERE movie_id IN (
              SELECT id
                FROM movies
                WHERE id IN (
                      SELECT movie_id
                        FROM ratings
                        WHERE rating >= 9.0)));

-- 11. write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in,
-- starting with the highest rated
SELECT title
  FROM movies
  JOIN ratings
    ON movies.id = ratings.movie_id
 WHERE movies.id IN (
       SELECT movie_id
         FROM stars
        WHERE person_id IN (
              SELECT id
              FROM people
              WHERE name = 'Chadwick Boseman'))
ORDER BY rating DESC
LIMIT 5;

-- 12. write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
SELECT title
  FROM movies
  JOIN stars
    ON movies.id = stars.movie_id

  JOIN people
    ON stars.person_id = people.id
 WHERE name = 'Bradley Cooper'

INTERSECT

SELECT title
  FROM movies
  JOIN stars
    ON movies.id = stars.movie_id

  JOIN people
    ON stars.person_id = people.id
 WHERE name = 'Jennifer Lawrence';

-- 13. write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT name
  FROM people
  JOIN stars
    ON people.id = stars.person_id

  JOIN movies
    ON stars.movie_id = movies.id
 WHERE name != 'Kevin Bacon'
   AND movie_id IN (
       SELECT movie_id
         FROM stars
         JOIN people
           ON stars.person_id = people.id
        WHERE (people.name = 'Kevin Bacon' AND people.birth = 1958));
