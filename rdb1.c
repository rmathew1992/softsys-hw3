#include <stdio.h>
#include "mongo.h"
#include "listFunctions.h"
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
	char target1[] = "brad pitt";
	char target2[] = "jamie foxx";	

	if (strcmp(target1, target2) == 0) { printf("same guy, dipshit\n"); exit(1); }

	printf("actor for inglorious basterds\n");
	struct node *root;
	root = getActors("inglorious basterds", conn);
	struct node *conductor;
	conductor = root;
	if (conductor != 0) {
		while (conductor->next != 0) {
			printf("%s\n", conductor->x);
			conductor = conductor->next;
		}
		printf("%s\n", conductor->x);
	}

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
		printf("%s\n", conductor2->x);
	}
	
	mongo_destroy(conn);
	return 0;

}
