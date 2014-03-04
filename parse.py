import string
import re

inputfile = open('actors.list','r')
outputfile = open('test.csv', 'w')
# for i in range(4): inputfile.next() Use this when you want to skip the introductory stuff

#Names start only with symbols,characters, and numbers
char = []
for i in range(33,127):
		char.append(chr(i))
full_list = {'temp':'movie'}
#A parse function returns actor names
actor = ['temp']
def parse_actor(text):
	temp = []
	if text.startswith(tuple(char)):
		columns = text.split("	",1)
		for i in columns:
			i = re.sub(r"\t", "", i)
			temp.append(i.split())
		actor[0] = ' '.join(temp.pop(0))
		movie = ' '.join(temp.pop(0))
		full_list[actor[0]] = [movie]
	elif text.startswith('	'): 
		text = text.strip()
		full_list[actor[0]].append(text)

for line in inputfile.readlines():
	parse_actor(line)

print full_list
inputfile.close()
