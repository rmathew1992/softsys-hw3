# March 2014
# Amanda Lee, Rachel Mathew, Mike Warner

# When this python program is run, it will look at a file called "movies.list" 
# that is downloaded from the imdb site. Before we ran this program, we deleted 
# extrangeous lines from the beginning and end. The program will take this list
# and search through the actorsToMovies database to find all actors that star in
# a specific movie. When the program is done running, there will be a moviesToActors
# database that maps movie titles to a list of the cast. 

import string
import re
import pymongo
from pymongo import MongoClient
from pymongo import ASCENDING

# This function takes a movie name and searches the actorsToMovies database
# to find all actors that have starred in that movie. These actors are 
# put in a list and inserted into a new mongo database that maps movies to 
# their casts.
# 
# movie 				a string representing the movie title
def findActors (movie):
	actors = aToM.find({"movies": movie}, fields={'_id':False, 'movies':False})
	tempDict = {}
	tempDict["movie"] = movie
	actorList = []
	for actor in actors:
		actorList.append(actor["actor"])
	tempDict["actors"] = actorList
	mToA.insert(tempDict)

# This function parses out the movie from a string.
#
# textLine				a string representing a line of text
def parseMovieName (textLine):
	columns = textLine.split(")", 1)
	movie = columns[0]
	movie = movie.strip()
	return movie

# The function takes a line of text and checks if it is a TV show or 
# a movie. If it is a movie, it is parsed and added to the database
#
# text 					a string representing a line of text
def parse_Movie(text):
	if (text[0]!='"'):
		movieTitle = parseMovieName(text)
		findActors(movieTitle)

# This function reads a given file line by line and feeds the lines to
# a parser. 
# 
# file_name				a string that represents the filename
def read_file(file_name):
	inputfile = open(file_name,'r')
	for line in inputfile.readlines():
		rawLine = line.decode('utf-8', 'replace')
		finalLine = rawLine.encode('utf-8')
		parse_Movie(finalLine)
	inputfile.close()

# opens the connection to the Mongo database
connection = MongoClient()
db = connection.sofSys3
aToM = db.actorsToMovies

# resets the moviesToActors database 
connection['sofSys3'].drop_collection('moviesToActors')
mToA = db.moviesToActors

read_file('movies.list')
print "DONE"