select * from Graph;
select count(*) from Word;
select 1 from Graph g left join Link l on g.Source=l.ID where l.path like "https://www.meetup.com/home/?suggested=true&source=EVENTS&customStartDate=2023-12-16T17%3A00%3A00-05%3A00";
-- INSERT INTO Link (Path) VALUES ("https://www.meetup.com/home/?suggested=true&source=EVENTS&customStartDate=2023-12-16T17%3A00%3A00-05%3A00");
-- SELECT ID FROM Link WHERE path LIKE "https://www.meetup.com/home/?suggested=true&source=EVENTS&customStartDate=2023-12-16T17%3A00%3A00-05%3A00";
-- INSERT OR IGNORE INTO Link (Path) VALUES ("https://www.example.com/");
-- SELECT ID FROM Link WHERE path LIKE "https://www.example.com/";

-- WITH ExistingRecord AS (
-- SELECT
--     Source, Destination
-- FROM
--     Graph
-- WHERE
--     Source = 1 AND Destination = 2 )
-- INSERT INTO Graph (Source, Destination, Count)
-- SELECT
--     1 AS Source,
--     2 AS Destination,
--     COALESCE(e.Count + 1, 1) AS NewCount
-- FROM
--     ExistingRecord e;

--     WITH ExistingRecord AS (
--     SELECT
--         Source,
--         Destination,
--         Count
--     FROM
--         Graph
--     WHERE
--         Source = 1
--         AND Destination = 2
-- )
-- INSERT INTO Graph (Source, Destination, Count)
-- SELECT
--     1 AS Source,
--     2 AS Destination,
--     COALESCE((SELECT Count FROM ExistingRecord) + 1, 1) AS NewCount;



INSERT INTO Graph (Source, Destination, Count)
VALUES (1,2, COALESCE((SELECT Count FROM Graph WHERE Source = 1 AND Destination = 2) + 1,1))
ON CONFLICT(Source, Destination)
DO UPDATE SET Count = Count + 1;


SELECT * FROM Graph;