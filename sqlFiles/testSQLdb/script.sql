-- SQLite does not require creating a database explicitly

-- CREATE TABLE Person (
--     ID INTEGER PRIMARY KEY,
--     Name NVARCHAR(60) NOT NULL CHECK(LENGTH(Name) > 3)
-- );

-- CREATE TABLE Car (
--     ID INTEGER PRIMARY KEY,
--     Made NVARCHAR(1024) NOT NULL CHECK(LENGTH(Made) > 3)
-- );

-- CREATE TABLE CarToPerson (
--     CarID INTEGER NOT NULL,
--     PersonID INTEGER NOT NULL,
--     Count INTEGER NOT NULL,
--     FOREIGN KEY (CarID) REFERENCES Car (ID) ON DELETE NO ACTION ON UPDATE NO ACTION,
--     FOREIGN KEY (PersonID) REFERENCES Person (ID) ON DELETE NO ACTION ON UPDATE NO ACTION
-- );

-- insert INTO Person(Name) VALUES (dudi);
-- insert INTO car(Made) VALUES ("volvo");
-- INSERT into CarToPerson(CarID, PersonID, Count) VALUES(
--     (SELECT id FROM car WHERE car.Made LIKE "volvo"),
--     (SELECT id FROM Person WHERE Name LIKE "dudi")
--     ,5);

-- DELETE FROM Car WHERE Made LIKE "volvo";
-- CREATE DATABASE test;

-- CREATE TABLE test.Person(
--     ID INTEGER PRIMARY KEY AUTO_INCREMENT NOT NULL,
--     Name NVARCHAR(60) NOT NULL,
--     CONSTRAINT C_Name CHECK(LENGTH(Name) > 3)
-- );

-- CREATE TABLE test.Car(
--     ID INTEGER PRIMARY KEY AUTO_INCREMENT NOT NULL,
--     Made NVARCHAR(1024) NOT NULL,
--     CONSTRAINT C_Made CHECK(LENGTH(Made) > 3)
-- );

-- CREATE TABLE test.CarToPerson(
--     CarID INTEGER NOT NULL,
--     PersonID INTEGER NOT NULL,
--     Count INTEGER NOT NULL,
--     FOREIGN KEY (CarID) REFERENCES Car (ID),
--         ON DELETE NO ACTION ON UPDATE NO ACTION,
--     FOREIGN KEY (PersonID) REFERENCES Person (ID),
--         ON DELETE NO ACTION ON UPDATE NO ACTION,
-- );

-- CREATE TABLE Person (
--     ID INTEGER PRIMARY KEY,
--     Name NVARCHAR(60) NOT NULL
-- );

-- CREATE TABLE Car (
--     ID INTEGER PRIMARY KEY,
--     OwnerID INTEGER REFERENCES Person(ID) ON DELETE NO ACTION ON UPDATE NO ACTION,
--     Model NVARCHAR(50) NOT NULL
-- );

-- -- Insert values into Person table
-- INSERT INTO Person (ID, Name) VALUES (1, 'John Doe');

-- -- Insert values into Car table
-- INSERT INTO Car (ID, OwnerID, Model) VALUES (101, 1, 'Toyota');
-- INSERT INTO Car (ID, OwnerID, Model) VALUES (102, 1, 'Honda');
-- DELETE FROM Person WHERE ID = 1;
-- INSERT INTO Person(Name) VALUES ("yosi");
-- INSERT INTO car(OwnerID,Model) VALUES (5,"skode");


-- Create tables
-- CREATE TABLE Person (
--     ID INTEGER PRIMARY KEY,
--     Name NVARCHAR(60) NOT NULL
-- );

-- CREATE TABLE Car (
--     ID INTEGER PRIMARY KEY NOT NULL,
--     OwnerID INTEGER NOT NULL,
--     Model NVARCHAR(50) NOT NULL,
--     FOREIGN KEY(OwnerID) REFERENCES Person(ID) ON DELETE NO ACTION ON UPDATE NO ACTION
-- );

-- -- Insert values
-- INSERT INTO Person (ID, Name) VALUES (1, 'John Doe');
-- INSERT INTO Car (ID, OwnerID, Model) VALUES (101, 3, 'Toyota');
-- INSERT INTO Car (ID, OwnerID, Model) VALUES (102, 1, 'Honda');

-- -- Attempt to delete the person with ID = 1
-- DELETE FROM Person WHERE ID = 1;


CREATE TABLE artist(
  artistid    INTEGER PRIMARY KEY, 
  artistname  TEXT
);

CREATE TABLE track(
  trackid     INTEGER, 
  trackname   TEXT, 
  trackartist INTEGER,
  FOREIGN KEY(trackartist) REFERENCES artist(artistid)
);