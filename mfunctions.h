#include <stdio.h>
#include "mongo.h"

static bson getMovieQuery(char *movie) {

	bson query;
	bson_init(&query);
	bson_append_string(&query, "title", movie);
	bson_finish(&query);
	return query;

}

static bson getActorQuery(char *actor) {

	bson query;
	bson_init(&query);
	bson_append_string(&query, "name", actor);
	bson_finish(&query);
	return query;
}

static bson getActorFields() {

	bson fields;
	bson_init(&fields);
	bson_append_int(&fields, "movie", 1);
	bson_append_int(&fields, "_id", 0);
	bson_finish(&fields);
	return fields;
}

static bson getMovieFields() {

	bson fields;
	bson_init(&fields);
	bson_append_int(&fields, "actor", 1);
	bson_append_int(&fields, "_id", 0);
	bson_finish(&fields);
	return fields;
}

