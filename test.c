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

struct node *append(struct node *list1, struct node *list2) {

	struct node *cond;
	cond = list1;
	printf("%s\n", cond->x);
	while (cond->next != 0) {
		cond = cond->next;
	}
	struct node *cond2;
	cond2 = list2;
	while(cond2->next != 0){
		cond =(struct node*)cond->x;
		cond2 = cond->next;
	}
	//cond->next = *list2;
	//cond->next = malloc(sizeof(struct node));
	//cond->next = list2;
	
	return list1;

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
	
	struct node *masterList;
	masterList = malloc(sizeof(struct node));
	masterList->x = actor2;
	masterList->next = 0;

	if (strcmp(actor1, actor2) == 0) { printf("same guy, dipshit\n"); exit(1); }

	struct node *actors;
	struct node *movies;
	movies = getMovies(actor1, conn);

	struct node *cond;
	cond = movies;
	
	int found;
	actors = getActors("inglorious basterds", conn);
	masterList = append(masterList, actors);
	//actors = getActors("inglorious basterds", conn );
	//while(actors->next != 0){
	//	actors = actors->next;
	//}	
	while (cond != NULL) {
		actors = getActors((char*)cond->x, conn);
	//	masterList = append(masterList, actors);
		//struct node *cond2;
		//cond2 = actors; 
		//found = searchfor(actor3,actors);
		//if(found ==1){
		//	printf("laughs laughs asglkjfal\n");
		//}
		cond = cond->next;
	}

	struct node *temp;
	temp = masterList;
	while (temp != NULL) {
		printf("%s\n", temp->x);
		temp = temp->next;
	}
	

	mongo_destroy(conn);
	return 0;

}
