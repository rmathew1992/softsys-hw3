import string
import re
import pymongo
from pymongo import MongoClient
from pymongo import ASCENDING

def findActors (movie):
	actors = aToM.find({"movies": movie}, fields={'_id':False, 'movies':False})
	tempDict = {}
	tempDict["movie"] = movie
	actorList = []
	for actor in actors:
		actorList.append(actor["actor"])
	tempDict["actors"] = actorList
	mToA.insert(tempDict)


def parseMovieName (textLine):
	columns = textLine.split("(", 1)
	movie = columns[0]
	movie = movie.strip()
	return movie

def parse_Movie(text):
	if (text[0]!='"'):
		movieTitle = parseMovieName(text)
		findActors(movieTitle)

def read_file(file_name):
	inputfile = open(file_name,'r')
	for line in inputfile.readlines():
		rawLine = line.decode('utf-8', 'replace')
		finalLine = rawLine.encode('utf-8')
		parse_Movie(finalLine)
	inputfile.close()


connection = MongoClient()
db = connection.sofSys3
aToM = db.actorsToMovies
mToA = db.moviesToActors

read_file('movies.list')
print "DONE"