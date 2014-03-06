#include <stdio.h>
#include "mongo.h"
#include "mfunctions.h"

struct node {
	const char *x;
	struct node *next;
};

struct node *getMovies(char *actorName, mongo *conn) {

	bson query = getActorQuery(actorName);
	bson fields = getActorFields();
	mongo_cursor * cursor = mongo_find(conn, "test.a", &query, &fields, 0,0,0);

	struct node *root;
	root = (struct node *) malloc(sizeof(struct node));
	root->next = 0;	
	struct node *conductor;
	conductor = root;

	bson *doc;
	while (mongo_cursor_next(cursor) == MONGO_OK) {
		doc = (bson *) mongo_cursor_bson(cursor);
		bson_iterator i[1];
		bson_iterator_init(i,doc);
		if (bson_iterator_next(i) != BSON_EOO) {
			conductor->x = bson_iterator_string(i);
		}
		while (bson_iterator_next(i) != BSON_EOO) {
			conductor->next = malloc(sizeof(struct node));
			conductor = conductor->next;
			conductor->x = bson_iterator_string(i);
		}
		conductor->next = 0;

	}
	mongo_cursor_destroy(cursor);
	return root;
}

struct node *getActors(char *movieName, mongo *conn) {

	//char movieName[] = "inglorious basterds";
	bson query = getMovieQuery(movieName);
	bson fields = getMovieFields();
	mongo_cursor * cursor = mongo_find(conn, "test.m", &query, &fields, 0,0,0);

	struct node *root;
	root = (struct node *) malloc(sizeof(struct node));
	root->next = 0;	
	struct node *conductor;
	conductor = root;

	bson *doc;
	while (mongo_cursor_next(cursor) == MONGO_OK) {
		doc = (bson *) mongo_cursor_bson(cursor);
		bson_iterator i[1];
		bson_iterator_init(i,doc);
		if (bson_iterator_next(i) != BSON_EOO) {
			conductor->x = bson_iterator_string(i);
			//printf("valueList: %s\n", conductor->x);
		}
		while (bson_iterator_next(i) != BSON_EOO) {
			conductor->next = malloc(sizeof(struct node));
			conductor = conductor->next;
			conductor->x = bson_iterator_string(i);
			//printf("valueList: %s\n", conductor->x);
		}

		conductor->next = 0;

	}
	mongo_cursor_destroy(cursor);
	return root;
}

