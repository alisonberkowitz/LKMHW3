# 6 Degrees of Separation Prototype
## Alison Berkowitz - Nathan Lintz
## Software Systems 2013

# Getting started
To process a file of actor names, go to the imdb website and find the actors.list file. Remove all headers from the file so that the top line is the first actor to movie relationship. Run parse.py to put all of the data in the database. You can run the make commands for BFS and Queries to get data from the database. Remember to change the source of parse and queries so they use the same mongo database. You can also run make seedDB && ./build/test_seed_DB to seed the database with some test data then run make BFS && ./build/BFS to run the breadth first traversal on some sample data.

# Dependencies
- Python
- Mongo -> pymongo and c drivers are used

# File Structure:
## Top Level Directories
### build/ - contains object files from compiled sources
### src/ - contains source files for all of our files
### test/ - contains test scripts for our files

##Files
## src/
### BreadthFirstSearch - Contains the query for running a breadth first traversal on the actors graph, test function for a dummy dataset is in the main
### Hashmap.c/Hashmap.h - Hashmap implementation we got from https://github.com/petewarden/c_hashmap
### Node.c/Node.h - Node model we used to represent an actor or a movie
### Parse.py - Python parser for the actors list dataset
### Queries.c/Queries.h - Contains queries for looking up an actor or movie by name
### Queue.c/Queue.h - Data structure for a queue used in the BFS

## test/
### dropDB.c - Wipes a collection from a database
### seedDB.c - Seeds the db with test data
### testHashmap.c - test script for the hashmap implementation
### testNode.c - test script for node model
### testQuery.c - test script for our actor and movie queries
### testQueue.c - test script for our queue implementation

