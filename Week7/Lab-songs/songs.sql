1. SELECT name FROM songs;

2. SELECT name FROM songs ORDER BY tempo;

3. SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;

4 SELECT name FROM songs WHERE (danceability >= 0.75 AND energy >= 0.75 AND valence >= 0.75);

5 SELECT avg(energy) AS Avg_energy FROM songs;

6 SELECT name from songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');

7 SELECT AVG(energy) AS Avg_Energy FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');

8 SELECT name FROM songs WHERE name LIKE "%feat.%";
