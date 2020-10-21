-- 2
select title from movies
where id in (select movie_id from stars where person_id in (select id from people where name = "Johnny Depp"))
and id in (select movie_id from stars where person_id in (select id from people where name = "Helena Bonham Carter"));

-- -- 1
-- select title from movies
-- where id in (select movie_id from stars
--     where person_id in
--     (select id from people where name in ("Johnny Depp", "Helena Bonham Carter"))
--     );

-- -- 3

-- select title, count(*) from movies
-- where id in (select movie_id from stars
--     where person_id in
--     (select id from people where name in ("Johnny Depp", "Helena Bonham Carter")));
-- group by title
-- having count(*) > 1;


-- -- 4
-- select title, count(*) from movies
-- where id in (select movie_id from stars where person_id in (select id from people where name = "Johnny Depp"))
-- and id in (select movie_id from stars where person_id in (select id from people where name = "Helena Bonham Carter"))
-- group by title
-- having count(*) > 1;