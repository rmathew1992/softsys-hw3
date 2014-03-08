/* 
March 2014
Amanda Lee, Rachel Mathew, Mike Warner

This file contains all the helper functions needed for rd1.c.  It also 
provides the structure for a linked list. 
*/

#include <stdio.h>
#include "mongo.h"
#include "mfunctions.h"

/*
The structure for a linked list. Each node contains a value and a pointer
to the next node. 
*/
struct node {
	const char *x;
	struct node *next;
};

/*
This function searches the moviesToActors database for all the movies that 
the given actor starred in. These movies are put into a linked list and the
root of the linked list is returned.

char *actorName			a pointer to the actors name
mongo *conn 			the mongo connection
*/
struct node *getMovies(char *actorName, mongo *conn) {
	bson query[1];
	mongo_cursor cursor[1];

	bson_init( query );
	bson_append_string( query, "actors", actorName);
	bson_finish( query );

	struct node *root;
	root = (struct node *) malloc(sizeof(struct node));
	root -> next = 0;
	struct node *conductor;
	conductor = root;

	mongo_cursor_init( cursor, conn, "sofSys3.moviesToActors" );
	mongo_cursor_set_query( cursor, query );

	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
		bson_iterator iterator[1];
		if ( bson_find( iterator, mongo_cursor_bson( cursor ), "movie" )) {
			conductor->x = bson_iterator_string(iterator);
			conductor->next = malloc(sizeof(struct node));
			conductor = conductor->next;
		}
		conductor->next = 0;
	}

	bson_destroy( query );
	mongo_cursor_destroy( cursor );
	return root;
}

/*
This function searches the actorsToMovies database for all the actors that 
star in the provided movie. Ther actors are put into a linked list and the
root is returned. 

char *movieName			a pointer to the movie title
mongo *conn 			the mongo connection
*/
struct node *getActors(char *movieName, mongo *conn) {
	bson query[1];
	mongo_cursor cursor[1];

	bson_init( query );
	bson_append_string( query, "movies", movieName);
	bson_finish( query );

	struct node *root;
	root = (struct node *) malloc(sizeof(struct node));
	root -> next = 0;
	struct node *conductor;
	conductor = root;

	mongo_cursor_init( cursor, conn, "sofSys3.actorsToMovies" );
	mongo_cursor_set_query( cursor, query );

	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
		bson_iterator iterator[1];
		if ( bson_find( iterator, mongo_cursor_bson( cursor ), "actor" )) {
			conductor->x = bson_iterator_string(iterator);
			conductor->next = malloc(sizeof(struct node));
			conductor = conductor->next;
		}
		conductor->next = 0;
	}

	bson_destroy( query );
	mongo_cursor_destroy( cursor );
	return root;
}

