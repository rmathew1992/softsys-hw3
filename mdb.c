#include <stdio.h>
#include "mongo.h"


static void insert(mongo *conn) {

	bson object1;
	bson_init(&object1);
	bson_append_string(&object1, "title", "Reservoir Dogs");
	bson_append_start_array(&object1, "actors");
		bson_append_string(&object1, "0", "Harvey Keitel");
		bson_append_string(&object1, "1", "Steve Buscemi");
	bson_append_finish_array (&object1);
	bson_finish(&object1);
	//bson_print(&object1);

	bson object2;
	bson_init(&object2);
	bson_append_string(&object2, "title", "Inglourious Basterds");
	bson_append_start_array(&object2, "actors");
		bson_append_string(&object2, "0", "Brad Pitt");
		bson_append_string(&object2, "1", "Christoph Waltz");
	bson_append_finish_array (&object2);
	bson_finish(&object2);
	//bson_print(&object2);

	bson object3;
	bson_init(&object3);
	bson_append_string(&object3, "title", "Django Unchained");
	bson_append_start_array(&object3, "actors");
		bson_append_string(&object3, "0", "Jamie Foxx");
		bson_append_string(&object3, "1", "Christoph Waltz");
	bson_append_finish_array (&object3);
	bson_finish(&object3);
	//bson_print(&object3);
		
	bson object4;
	bson_init(&object4);
	bson_append_string(&object4, "name", "Brad Pitt");
	bson_append_start_array(&object4, "movies");
		bson_append_string(&object4, "0", "Inglourious Basterds");
	bson_append_finish_array (&object4);
	bson_finish(&object4);
	//bson_print(&object2);

	bson object5;
	bson_init(&object5);
	bson_append_string(&object5, "name", "Christoph Waltz");
	bson_append_start_array(&object5, "movies");
		bson_append_string(&object5, "0", "Inglourious Basterds");
		bson_append_string(&object5, "1", "Django Unchained");
	bson_append_finish_array (&object5);
	bson_finish(&object5);

	bson object6;
	bson_init(&object6);
	bson_append_string(&object6, "name", "Harvey Keitel");
	bson_append_start_array(&object6, "movies");
		bson_append_string(&object6, "0", "Reservoir Dogs");
	bson_append_finish_array (&object6);
	bson_finish(&object6);

	mongo_insert(conn, "test2.m", &object1,0);
	mongo_insert(conn, "test2.m", &object2,0);
	mongo_insert(conn, "test2.m", &object3,0);
	mongo_insert(conn, "test2.a", &object4,0);
	mongo_insert(conn, "test2.a", &object5,0);
	mongo_insert(conn, "test2.a", &object6,0);

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
