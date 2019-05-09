PRAGMA foreign_keys=on;

CREATE TABLE artists (
Id integer PRIMARY KEY AUTOINCREMENT, 
Name TEXT UNIQUE,
AlbumsCount integer
);

INSERT INTO artists (Name) VALUES (NULL);

CREATE TABLE albums (
Id integer PRIMARY KEY AUTOINCREMENT, 
Title TEXT,
ArtistId integer,
TracksCount integer,
FOREIGN KEY (ArtistId) REFERENCES artists(Id)
);

INSERT INTO albums (ArtistId, Title) VALUES (1, NULL);

CREATE TABLE genres (
Id integer PRIMARY KEY AUTOINCREMENT, 
Name TEXT UNIQUE
);

INSERT INTO genres (Name) VALUES (NULL);

CREATE TABLE tracks (
 Id INTEGER PRIMARY KEY AUTOINCREMENT, 
 Name TEXT, 
 Num INTEGER, 
 AlbumId INTEGER, 
 GenreId INTEGER, 
 Filename TEXT,
 CoverFile TEXT,
FOREIGN KEY (AlbumId) REFERENCES albums(Id)
FOREIGN KEY (GenreId) REFERENCES genres(Id)
);
 
CREATE INDEX TracksIndex ON tracks (Name);
CREATE INDEX AlbumsIndex ON albums (Title);
CREATE INDEX ArtistsIndex ON artists (Name);

CREATE VIEW TracksView AS 
SELECT
 artists.Name AS artist,
 albums.Title AS album,
 tracks.Id AS trackid,
 tracks.Num AS tracknum, 
 tracks.Name AS trackname,
 tracks.Filename AS filename, 
 genres.Name AS genres,
 tracks.AlbumId AS albumid,
 tracks.CoverFile AS cover,
 albums.TracksCount as albumTrackCount
FROM
 tracks
INNER JOIN albums ON albums.Id = tracks.AlbumId
INNER JOIN artists ON artists.Id = albums.ArtistId
INNER JOIN genres ON genres.Id = tracks.GenreId;
