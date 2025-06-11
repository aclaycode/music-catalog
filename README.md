# Music Catalog

This C program manages a simple music catalog, allowing users to search for songs by artist, find the artist for a given song, and print all songs by a particular artist. It uses arrays of structs to store song and artist data, and includes functions to perform various lookups and operations on the catalog.

## Features

- Check if a given artist has any songs in the catalog
- Print all songs by a specific artist
- Find the artist of a specific song
- Handles missing data gracefully

## Files

- `music_catalog.c` — Main source file containing the logic and functions

## How to Compile

Use `gcc` to compile the program:

```bash
gcc -o music_catalog music_catalog.c
```

This will create an executable named `music_catalog`.

## How to Run

```bash
./music_catalog music_catalog_data.txt
```

## Example Output

```
***Testing the isArtistInCatalog() function***
There is at least one Pink Floyd song in the catalog
There are no Jon Kuhl songs in the catalog

***Testing the printSongsByArtist() function***
Songs by Bruce Springsteen:
Bobby Jean
Born in the U.S.A.
...

Songs by U2:
Beautiful Day
Elevation
...

Songs by Jon Kuhl

***Testing the findArtistForSong() function***
The artist for In The Flesh is: Pink Floyd
The artist for Summertime Blues could not be found
```

## Notes

- The song and artist data are currently hardcoded in the source .txt file.
- Functions are written to be modular for ease of maintenance and potential future expansion.
- The program handles cases where the artist or song is not found by printing appropriate messages.
