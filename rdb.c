#include <stdio.h>
#include "mongo.h"


static void insert(mongo *conn) {

	bson query;
	bson_init(&query);
	bson_append_string(&query, "title", "inglorious basterds");
	bson_finish(&query);

	bson fields;
	bson_init(&fields);
	bson_append_int(&fields, "actor", 1);
	bson_append_int(&fields, "_id", 0);
	bson_finish(&fields);
	
	mongo_cursor * cursor = mongo_find(conn, "test.m", &query, &fields, 0,0,0);

	bson *doc;
	while (mongo_cursor_next(cursor) == MONGO_OK) {
		doc = (bson *) mongo_cursor_bson(cursor);
		
		bson_iterator i[1];
		bson_type type;
		const char * key;
		
		bson_iterator_init(i,doc);
		while (bson_iterator_next(i) != BSON_EOO) {
			printf("value: %s\n", bson_iterator_string(i));
		}

	}
	mongo_cursor_destroy(cursor);

}

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

	insert(conn);
	mongo_destroy(conn);
	return 0;

}
