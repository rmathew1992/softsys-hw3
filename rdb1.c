/* 
March 2014
Amanda Lee, Rachel Mathew, Mike Warner

This file starts a connection to the mongo database and searches the database
for the cast of Inglourious Basterds that came out in 2009. It also finds all 
movies that Brad Pitt has been cast in. These are examples of how we would search
the databases. 

The only problem about the queries right now are that the movie query has to be
of the format that "movie title (year" and the actor has to be "last, first".
Sometimes the actor will need a roman numeral at the end because multiple actors
have the same name. This is a prototype but in the future the query would take 
this into account so that the user could just enter in a name and an actor.
*/

#include <stdio.h>
#include "mongo.h"
#include "listFunctionsFinal.h"
#include <string.h>

int main() {

	mongo conn[1];
	int status = mongo_client(conn, "127.0.0.1", 27017);
	
	if (status != MONGO_OK) {
		switch(conn->err) {
			case MONGO_CONN_NO_SOCKET: 	printf("no socket\n"); return 1;
			case MONGO_CONN_FAIL: 		printf("connection failed\n"); return 1;
			case MONGO_CONN_NOT_MASTER: 	printf("not master\n"); return 1;
		}
	}
	char target1[] = "Pitt, Brad";
	char target2[] = "Foxx, Jamie";	

	if (strcmp(target1, target2) == 0) { printf("same guy, dipshit\n"); exit(1); }

	/* 
	The program is given a movie and it finds the cast of that movie in the 
	form of a linked list.
	*/
	printf("actor for inglorious basterds\n");
	struct node *root;
	root = getActors("Inglourious Basterds (2009", conn);
	struct node *conductor;
	conductor = root;
	if (conductor != 0) {
		while (conductor->next != 0) {
			printf("%s\n", conductor->x);
			conductor = conductor->next;
		}
		printf("%s\n", conductor->x);
	}
	
	/* 
	The program is given an actor and it finds all the movies that person has 
	starred in, in the form of a linked list. 
	*/
	printf("movies for brad pitt\n");
	struct node *root2;
	root2 = getMovies(target1, conn);
	struct node *conductor2;
	conductor2 = root2;
	if (conductor2 != 0) {
		while(conductor2->next != 0) {
			printf("%s\n", conductor2->x);
			conductor2 = conductor2->next;
		}
		printf("%s\n", conductor->x);
	}
	
	mongo_destroy(conn);
	return 0;

}
