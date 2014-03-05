import string
import re

def parse_actor(text, dictionary, initial):
	
	#A parse function returns actor names
	temp = []
	if text.startswith(tuple(char)):
		columns = text.split("	",1)
		for i in columns:
			i = re.sub(r"\t", "", i)
			temp.append(i.split())
		initial[0] = ' '.join(temp.pop(0))
		movie = ' '.join(temp.pop(0))
		dictionary[initial[0]] = [movie]
	elif text.startswith('	'): 
		text = text.strip()
		dictionary[initial[0]].append(text)

def read_file(file_name, parsed):
	inputfile = open(file_name,'r')
	initial = ['temp']
	for line in inputfile.readlines():
		parse_actor(line, parsed, initial)
	inputfile.close()
	return parsed

#Names start only with symbols,characters, and numbers
char = []
for i in range(33,127):
	char.append(chr(i))

actors = {'temp':'movie'}
actresses = {'temp': 'movie'}


# List files must have excess information trimmed out
actors = read_file('actors.list', actors)
actresses = read_file('actresses.list', actresses)
print actresses
