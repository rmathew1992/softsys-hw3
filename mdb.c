#include <stdio.h>
#include "mongo.h"

static void insert(mongo *conn) {

	bson object1;
	bson_init(&object1);
	bson_append_string(&object1, "title", "resevoir dogs");
	bson_append_string(&object1, "actor", "harvey keitel");
	bson_append_string(&object1, "actor", "steve buscmemi");
	bson_finish(&object1);
	//bson_print(&object1);

	bson object2;
	bson_init(&object2);
	bson_append_string(&object2, "title", "inglorious basterds");
	bson_append_string(&object2, "actor", "brad pitt");
	bson_append_string(&object2, "actor", "christoph waltz");
	bson_finish(&object2);
	//bson_print(&object2);

	bson object3;
	bson_init(&object3);
	bson_append_string(&object3, "title", "django unchained");
	bson_append_string(&object3, "actor", "christoph waltz");
	bson_append_string(&object3, "actor", "jamie foxx");
	bson_finish(&object3);
	//bson_print(&object3);
		
	bson object4;
	bson_init(&object4);
	bson_append_string(&object4, "name", "brad pitt");
	bson_append_string(&object4, "movie", "inglorious basterds");
	bson_finish(&object4);
	//bson_print(&object2);

	bson object5;
	bson_init(&object5);
	bson_append_string(&object5, "name", "christoph waltz");
	bson_append_string(&object5, "movie", "inglorious basterds");
	bson_append_string(&object5, "movie", "django unchained");
	bson_finish(&object5);

	bson object6;
	bson_init(&object6);
	bson_append_string(&object6, "name", "harvey keitel");
	bson_append_string(&object6, "movie", "resevoir dogs");
	bson_finish(&object6);

	mongo_insert(conn, "test.m", &object1,0);
	mongo_insert(conn, "test.m", &object2,0);
	mongo_insert(conn, "test.m", &object3,0);
	mongo_insert(conn, "test.a", &object4,0);
	mongo_insert(conn, "test.a", &object5,0);
	mongo_insert(conn, "test.a", &object6,0);

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
