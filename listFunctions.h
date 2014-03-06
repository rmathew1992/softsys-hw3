#include <stdio.h>
#include "mongo.h"
#include "mfunctions.h"

struct node {
	const char *x;
	struct node *next;
};

struct node *getMovies(char *actorName, mongo *conn) {
	bson query[1];
	mongo_cursor cursor[1];

	bson_init( query );
	//bson_append_string(query, "actor")
	bson_append_string( query, "actors", actorName);
	bson_finish( query );

	struct node *root2;
	root2 = (struct node *) malloc(sizeof(struct node));
	root2 -> next = 0;
	struct node *conductor2;
	conductor2 = root2;

	//mongo_cursor_init(cursor, conn, "test.m")
	mongo_cursor_init( cursor, conn, "test2.m" );
	mongo_cursor_set_query( cursor, query );

	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
		bson_iterator iterator[1];
		if ( bson_find( iterator, mongo_cursor_bson( cursor ), "title" )) {
			conductor2->x = bson_iterator_string(iterator);
			conductor2->next = malloc(sizeof(struct node));
			conductor2 = conductor2->next;
		}
		conductor2->next = 0;
	}

	bson_destroy( query );
	mongo_cursor_destroy( cursor );
	return root2;
}

struct node *getActors(char *movieName, mongo *conn) {

	//char movieName[] = "inglorious basterds";

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

	mongo_cursor_init( cursor, conn, "test2.a" );
	mongo_cursor_set_query( cursor, query );

	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
		bson_iterator iterator[1];
		if ( bson_find( iterator, mongo_cursor_bson( cursor ), "name" )) {
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

