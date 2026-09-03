===============================================================
              ITERATOR DESIGN PATTERN — UML
              Example: Music Playlist
===============================================================


                         <<interface>>
                         Iterator<T>
                    +----------------------+
                    | + hasNext(): bool    |
                    | + next(): T          |
                    +----------+-----------+
                               ^
                               |
                         implements
                               |
                    +----------+-----------+
                    |                      |
                    | PlaylistIterator     |
                    +----------------------+
                    | - playlist: Playlist|
                    | - index: int        |
                    +----------------------+
                    | + hasNext(): bool   |
                    | + next(): Song      |
                    +----------------------+
                               |
                               | has-a
                               | / uses
                               v
                    +----------------------+
                    |       Playlist       |
                    +----------------------+
                    | - songs: vector<Song>|
                    +----------------------+
                    | + addSong()          |
                    | + createIterator()  |
                    +----------+-----------+
                               |
                               | creates
                               v
                    +----------------------+
                    | PlaylistIterator     |
                    +----------------------+


                    <<interface>>
                    Iterable / Aggregate
                    +----------------------+
                    | + createIterator()  |
                    |   : Iterator<Song>   |
                    +----------+-----------+
                               ^
                               |
                         implements
                               |
                               |
                    +----------+-----------+
                    |       Playlist       |
                    +----------------------+


===============================================================
                    RELATIONSHIPS
===============================================================

1. Playlist  ────────implements────────>  Iterable

   Meaning:
   Playlist ek aisa collection hai jo iterator provide kar
   sakta hai.

   "Playlist IS-A Iterable"

   Isliye UML mein:

             Playlist
                 |
                 | implements
                 v
             Iterable


---------------------------------------------------------------

2. PlaylistIterator ─────implements─────> Iterator<Song>

   Meaning:
   PlaylistIterator actual mein playlist ke songs ko one-by-one
   traverse karne ka kaam karta hai.

   "PlaylistIterator IS-A Iterator"

             PlaylistIterator
                    |
                    | implements
                    v
                 Iterator


---------------------------------------------------------------

3. PlaylistIterator ─────────has-a────────> Playlist

   Meaning:
   Iterator ko pata hona chahiye ki kis collection ke andar
   traverse karna hai.

   Isliye iterator ke paas Playlist ka reference hota hai.

             PlaylistIterator
                    |
                    | has-a
                    v
                 Playlist


---------------------------------------------------------------

4. Playlist ─────────creates────────> PlaylistIterator

   Meaning:
   Client directly iterator ka object nahi banata.

   Client bolta hai:

        playlist.createIterator()

   Aur Playlist internally iterator bana kar return karti hai.


===============================================================
                  SABSE IMPORTANT IDEA
===============================================================

Normally agar hum collection ke andar iterate karna chahein:

        for(int i = 0; i < songs.size(); i++) {
            ...
        }

Toh CLIENT ko pata hona chahiye:

        - songs vector mein stored hain
        - index kaise use karna hai
        - collection ka internal structure kya hai


Iterator Pattern bolta hai:

        "Client ko collection ke andar ka structure mat dikhao."

        Client ko sirf ek simple interface do:

                hasNext()
                next()


===============================================================
                     WITHOUT ITERATOR
===============================================================

                    Client
                       |
                       | directly accesses
                       v
                  Playlist
                       |
                       v
                  vector<Song>

Client ko pata hai:

        vector hai
        index hai
        size() hai
        traversal kaise karna hai


Problem:

        Client tightly coupled ho gaya Playlist ke
        internal data structure ke saath.


===============================================================
                      WITH ITERATOR
===============================================================

                    Client
                       |
                       | asks for
                       v
                  Playlist
                       |
                       | creates
                       v
              PlaylistIterator
                       |
                       | traverses
                       v
                  Playlist


Client ko bas itna pata hai:

        Iterator *it = playlist.createIterator();

        while(it->hasNext()) {
            Song song = it->next();
        }


Client ko ye nahi pata:

        vector use hua hai ya array
        linked list use hui hai
        tree use hua hai
        index kaise maintain ho raha hai


===============================================================
                     FLOW OF EXECUTION
===============================================================

Step 1:

Client ke paas Playlist hai.

        Playlist playlist;


Step 2:

Client iterator maangta hai.

        Iterator<Song>* it = playlist.createIterator();


Step 3:

Playlist ek PlaylistIterator create karti hai.

        Playlist
            |
            | createIterator()
            v
        PlaylistIterator


Step 4:

Iterator ke andar:

        playlist reference
        index = 0

        PlaylistIterator
        +------------------+
        | playlist         |
        | index = 0        |
        +------------------+


Step 5:

Client poochta hai:

        it->hasNext()


Iterator check karta hai:

        index < playlist.size()


Agar TRUE:

        next element available hai.


Step 6:

Client bolta hai:

        it->next()


Iterator:

        current song return karega
        index++

Example:

        index = 0

        next()
          |
          v
        Song 0
        index = 1


        next()
          |
          v
        Song 1
        index = 2


        next()
          |
          v
        Song 2
        index = 3


===============================================================
                       COMPLETE UML
===============================================================


                         <<interface>>
                            Iterator
                    +-----------------------+
                    | + hasNext(): bool     |
                    | + next(): Song        |
                    +-----------^-----------+
                                |
                                | implements
                                |
                    +-----------+-----------+
                    |   PlaylistIterator    |
                    +-----------------------+
                    | - playlist: Playlist* |
                    | - index: int          |
                    +-----------------------+
                    | + hasNext(): bool     |
                    | + next(): Song        |
                    +-----------+-----------+
                                |
                                |
                                | has-a
                                |
                                v
                    +-----------------------+
                    |       Playlist        |
                    +-----------------------+
                    | - songs: vector<Song> |
                    +-----------------------+
                    | + addSong()           |
                    | + createIterator()   |
                    +-----------^-----------+
                                |
                                | implements
                                |
                    +-----------+-----------+
                    |      <<interface>>    |
                    |       Iterable        |
                    +-----------------------+
                    | + createIterator()   |
                    |   : Iterator<Song>    |
                    +-----------------------+


                    +-----------------------+
                    |        Client         |
                    +-----------------------+
                    | + traverse()         |
                    +-----------+-----------+
                                |
                                | uses
                                v
                    +-----------------------+
                    |       Iterator        |
                    +-----------------------+


===============================================================
                 KAUN KISKI RESPONSIBILITY?
===============================================================

1. Iterable / Aggregate
   --------------------

   Responsibility:

   "Mere collection ko traverse karne ke liye iterator
    kaise milega?"

   Example:

        createIterator()


---------------------------------------------------------------

2. Playlist
   --------

   Responsibility:

   Actual data ko store karna.

        songs

   Aur iterator provide karna.

        createIterator()


---------------------------------------------------------------

3. Iterator
   --------

   Responsibility:

   Traversal ke rules define karna.

        hasNext()
        next()


---------------------------------------------------------------

4. PlaylistIterator
   -----------------

   Responsibility:

   Actual traversal perform karna.

        current index maintain karna
        next element dena
        end check karna


---------------------------------------------------------------

5. Client
   ------

   Responsibility:

   Collection ko traverse karna.

   Lekin collection ke internal structure ko
   directly access NAHI karna.


===============================================================
                  WHY DO WE NEED THIS PATTERN?
===============================================================

Suppose kal Playlist ka internal structure change ho gaya:

        vector<Song>

             ↓

        linked list<Song>


Agar client directly vector access kar raha tha:

        client ka code break/change hoga.


Lekin Iterator Pattern mein:

        Client
           |
           v
        Iterator
           |
           v
        Collection


Client ko farak hi nahi padega ki andar:

        vector hai
        array hai
        linked list hai
        tree hai


Iterator same interface provide karega:

        hasNext()
        next()


Isliye CLIENT aur COLLECTION loosely coupled rehte hain.


===============================================================
                    INTERVIEW ONE-LINER
===============================================================

Iterator Design Pattern ek collection ke internal structure ko
expose kiye bina uske elements ko sequentially traverse karne
ka standard way provide karta hai.


===============================================================
                  REAL-LIFE ANALOGY
===============================================================

Imagine Spotify ki playlist:

        Playlist
        -------------------------
        Song A
        Song B
        Song C
        Song D
        -------------------------


Tum Spotify se nahi poochte:

        "Andar songs kis data structure mein stored hain?"


Tum bas bolte ho:

        next song?


Spotify:

        Song A

Tum:

        next song?


Spotify:

        Song B

Tum:

        next song?


Spotify:

        Song C


Yahi Iterator ka concept hai.

Collection = Playlist

Iterator = "Next song dene wala mechanism"

Client = Tum


===============================================================
                    CORE MEMORY TRICK
===============================================================

Collection ka kaam:

        DATA RAKHNA


Iterator ka kaam:

        DATA GHUMANA / TRAVERSE KARNA


Client ka kaam:

        DATA USE KARNA


Yaad rakho:

        Collection
             |
             | creates
             v
          Iterator
             |
             | traverses
             v
          Elements


Main goal:

        "Collection ke andar ka structure hide karo,
         aur traversal ka simple interface do."


===============================================================