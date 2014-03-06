#include <stdio.h>
#include "mongo.h"
#include "listFunctions.h"
#include <string.h>

int searchfor(char *actor, struct node *list) {

	struct node *cond;
	cond = list;
	while(cond != NULL) {
		if (strcmp(actor, cond->x) == 0) return 1;
		cond = cond->next;
	} 
	return 0;
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
	char actor1[] = "brad pitt";
	char actor2[] = "jamie foxx";
	char actor3[] = "christoph waltz";	

	if (strcmp(actor1, actor2) == 0) { printf("same guy, dipshit\n"); exit(1); }

	struct node *actors;
	struct node *movies;
	movies = getMovies(actor1, conn);

	struct node *cond;
	cond = movies;
	
	int found;
	while (cond != NULL) {
		actors = getActors((char*)cond->x, conn);
		struct node *cond2;
		cond2 = actors; 
		found = searchfor(actor3,actors);
		if(found ==1){
			printf("laughs laughs asglkjfal\n");
		}
		cond = cond->next;
	}

	printf("%i\n", found);	

	mongo_destroy(conn);
	return 0;

}
