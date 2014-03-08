# March 2014
# Amanda Lee, Rachel Mathew, Mike Warner

# This program takes "actors.list" and "actresses.list" (with the extraneous lines 
# removed beforehand) and parses the data to add to a database. For each actor/
# actress the program parses out a list of movies (that are associated with a year)
# that is also stored in the database. TV shows are not included. The end result of 
# this program is a database called actorsToMovies that is indexed by actor name
# and the movies (to make searching faster).

import string
import re
import pymongo
from pymongo import MongoClient
from pymongo import ASCENDING

# This function takes in a dictionary that was created during the parsing
# process and searches through it for new entries to add to the mongo 
# database. It makes sure to exclude the temporary entry that the dictionary
# was initialized with. The dictionary entry is put into a new dictionary 
# with different keys so that it can be inserted into mongo. 
#
# actorD			a dictionary with the key being the actor name
#					and the value being a list of movies. 
def dictToJson (actorD):
	tempDict = {}
	for key in actorD:
		if (key!= 'temp'):
			tempDict["actor"] = key
			tempDict["movies"] = actorD[key]

			aToM.insert(tempDict)


# This function takes the lines from the file and adds the movies as 
# values for the corresponding actors. When the next actor is parsed
# the finished actor is placed in the database. 
#
# text 				a string that is a line from file
# dictionary		dictionary that holds that actor/movie data
# initial 			the current actor that is being parsed
def parse_actor(text, dictionary, initial):
	movieToParse = text
	if text.startswith(tuple(char)):
		dictToJson (dictionary)
		del dictionary[initial[0]]

		initial[0], movieToParse = parseActorName(text)

		dictionary[initial[0]] = []

	movie = parseMovieName (movieToParse)
	if (movie!="" and movie[0]!='"'):
			dictionary[initial[0]].append(movie)


# This function takes a line string (that includes an actor name) and
# parses out the actor name and first movie they star in. It returns a 
# tuple with a string that is the actor name and the movie title. 
#
# textLine			a string that is a line from the file. 
def parseActorName (textLine):
	temp = []
	columns = textLine.split("	",1)
	for i in columns:
		i = re.sub(r"\t", "", i)
		temp.append(i.split())

	actor = ' '.join(temp.pop(0))
	movie = ' '.join(temp.pop(0))
	return actor, movie


# This function takes a line string (that does not have an actor name)
# and parses out the movie name. This is done by stripping all the white
# space and cutting off the string after the year. It returns a string
# that is the movie title with the year.
#
# textLine 			a string that is a line from the file
def parseMovieName (textLine):
	columns = textLine.split(")", 1)
	movie = columns[0]
	movie = movie.strip()
	return movie


# This function takes in a file name and a temporary dictionary.
# The file is read line by line, and each line is passed to a parsing
# function. It returns a dictionary. 
#
# file_name			a string that is the file name
# parsed			a temporary dictionary that is passed directly
#					to the parsing function
def read_file(file_name, parsed):
	inputfile = open(file_name,'r')
	initial = ['temp']
	for line in inputfile.readlines():

		# the line string needs to be decoded to replace characters
		# that are not valid and cannot be added to the database
		rawLine = line.decode('utf-8', 'replace')
		finalLine = rawLine.encode('utf-8')

		parse_actor(finalLine, parsed, initial)
	inputfile.close()
	return parsed


# starts the connection to Mongo
connection = MongoClient()
db = connection.sofSys3

# resets the actorsToMovies collection and accesses it
connection['sofSys3'].drop_collection('actorsToMovies')
aToM = db.actorsToMovies

# indexing for the collection
aToM.create_index([("actor", ASCENDING)])
aToM.ensure_index("movies")

# Names start only with symbols,characters, and numbers
char = []
for i in range(33,127):
	char.append(chr(i))

# temporary dictionaries to pass into read_file function
actors = {'temp':'movie'}
actresses = {'temp': 'movie'}

# List files must have excess information trimmed out
actors = read_file('actors.list', actors)
actresses = read_file('actresses.list', actresses)
print "DONE"