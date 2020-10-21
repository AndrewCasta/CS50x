select title, ratings.rating from movies
join ratings on movies.id = ratings.movie_id
where year = 2010
ORDER BY ratings.rating desc, title asc;

-- Movies that do not have ratings should not be included in the result.
-- doesn't look like there are any?