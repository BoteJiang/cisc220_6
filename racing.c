#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

//Bote Jiang 10126930
//Jingyuan Chen 10152291
//Guanlin Lu 10199220


#define CARNUM 5
int CARSTEPS[CARNUM];
int GAMEOVER = 0;



/*The car threads, use rand() function from stdio.h and usleep() function from unistd.h to
implement the AI.*/
void* car_thread (void *m)
{

	int threadId = *((int *)m);

	if(threadId == 0){    //car 1read input from user. Move car 1 one space forward for each enter pressed by the user.
		while( GAMEOVER == 0){

			while(getchar() != '\n');
			CARSTEPS[threadId]++;
			if(CARSTEPS[threadId] == 40){

				GAMEOVER = 1;   //when one car move 40 steps game over
			}

		}
	}
	else{
		//other cars use rand() function from stdio.h and usleep() function
		while( GAMEOVER == 0){

			int temp = rand()%101;
			usleep(temp*1000);
			CARSTEPS[threadId]++;
			if(CARSTEPS[threadId] == 40){

				GAMEOVER = 1; //when one car move 40 steps game over
			}
		}
	}

	pthread_exit (NULL);
}


 /*The print thread,This game supports 5 frames per seconds (5 fps)*/
 void* print_thread (void *m)
{
	int index,jndex;
	int steps;
	int winner = -1;
	while(1){

		for(index =0; index<CARNUM; index++){

			steps = CARSTEPS[index];
			for(jndex = 0; jndex < steps; jndex++)
				printf("%c",'~');
			printf("%s","|->");
			for(jndex = 0; jndex < 40-steps ; jndex++)
				printf("%c",' ');
			printf("# Lane %d #\n", index + 1);
			if(steps == 40){
				winner = index;   //find the winner
			}
		}
		if(winner != -1){

			printf("Player %d WINS\n", winner+1);  //when some one win
			break;
		}
		else{
			system("clear");   //clear the screen and sleep for 20 mileseconds
			usleep(20000);
		}

	}


	pthread_exit (NULL);

}


/*when the program start show the message*/
void first_print(){

	int index,jndex;
	printf("Welcome to CISC220 Racing Arena\nHit Enter to move forward\n");
	for(index =0; index<CARNUM; index++){    //print five cars

		printf("%s","|->");
		for(jndex = 0; jndex < 40 ; jndex++)
			printf("%c",' ');
		printf("# Lane %d #\n", index + 1);
	}

}


int main (int argc,char *argv[])
{

	int index;
	int threadIds[CARNUM];
	pthread_t carThreads[CARNUM] ;
	pthread_t printThread;

	first_print();
	while(getchar() != '\n');  //when enter start game

	//create five thread for car
	for(index = 0;index<CARNUM; index++){

		threadIds[index] = index;
		CARSTEPS[index] = 0;

		if (pthread_create(&carThreads[index], NULL, car_thread, (void *)&threadIds[index]))
		{

			exit (1);
		}

	}
	//create a print thread for print
	if (pthread_create(&printThread, NULL, print_thread, NULL))
	{

		exit (1);
	}

	//wait the threads exit
	for(index =0; index<CARNUM; index++){

		pthread_join (carThreads[index], NULL);

	}
	pthread_join (printThread, NULL);
	return 0;

}
