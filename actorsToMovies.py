import string
import re
import pymongo
from pymongo import MongoClient
from pymongo import ASCENDING

def dictToJson (actorD):
	tempDict = {}
	for key in actorD:
		if (key!= 'temp'):
			tempDict["actor"] = key
			tempDict["movies"] = actorD[key]

			aToM.insert(tempDict)

def parse_actor(text, dictionary, initial):
	movieToParse = text
	#A parse function returns actor names
	if text.startswith(tuple(char)):
		dictToJson (dictionary)
		del dictionary[initial[0]]

		initial[0], movieToParse = parseActorName(text)

		dictionary[initial[0]] = []

	movie = parseMovieName (movieToParse)
	if (movie!="" and movie[0]!='"'):
			dictionary[initial[0]].append(movie)

def parseActorName (textLine):
	temp = []
	columns = textLine.split("	",1)
	for i in columns:
		i = re.sub(r"\t", "", i)
		temp.append(i.split())

	actor = ' '.join(temp.pop(0))
	movie = ' '.join(temp.pop(0))
	return actor, movie

def parseMovieName (textLine):
	columns = textLine.split("(", 1)
	movie = columns[0]
	movie = movie.strip()
	return movie

def read_file(file_name, parsed):
	inputfile = open(file_name,'r')
	initial = ['temp']
	for line in inputfile.readlines():
		rawLine = line.decode('utf-8', 'replace')
		finalLine = rawLine.encode('utf-8')
		parse_actor(finalLine, parsed, initial)
	inputfile.close()
	return parsed


connection = MongoClient()
db = connection.sofSys3
aToM = db.actorsToMovies
aToM.create_index([("actor", ASCENDING), ("movies", ASCENDING)])
#Names start only with symbols,characters, and numbers
char = []
for i in range(33,127):
	char.append(chr(i))

actors = {'temp':'movie'}
actresses = {'temp': 'movie'}


# List files must have excess information trimmed out
actors = read_file('actors.list', actors)
actresses = read_file('actresses.list', actresses)
print "DONE"