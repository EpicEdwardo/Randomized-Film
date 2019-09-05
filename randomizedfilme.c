#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXSEGMENT 300
#define CUTSEGMENT 24

int main(int argc, char **argv) {
  if(arc < 3){
	  fprintf(stderr, "need more arguments\n");
	  exit(1);
  }
  
  FILE *fp = fopen("list.txt", w);
  int length = strol(argv[2], NULL, 10);
  for(int i = 0; i < 10; i++){
	  int r = fork();
	  if (r < 0){
		  perror("fork");
      return -1;
	  } else if (r==0){
		  char path[6];
		  snprintf(path, sizeof(path), "%d.mp4",i);
		  char write[13];
		  snprintf(write, sizeof(write), "file '%s'\n",path);
		  int randomlocation = rand() % (length - MAXSEGMENT);
		  int randomchunk = rand() % (MAXSEGMENT);
		  fwrite(write,13,1,fp);
		  // first line gets the length of randomlocation/randomchunk
		  int length = snprintf( NULL, 0, "%d", randomlocation );
		  char location[length+1];
		  snprintf( location, length + 1, "%d", randomlocation );
		  
		  int length2 = snprintf( NULL, 0, "%d", randomchunk );
		  char chunk[length2+1];
		  snprintf( randomchunk, length2 + 1, "%d", randomchunk );
		  
		  char *arguments[] = {"ffmpeg", "-ss", "-i", argv[1], location, "-t", chunk, path, NULL};
		  
		  execl("ffmpeg", "ffmpeg", arguments, NULL);
		  exit(1);
	} else {
    }
  }
  
  for (int k = 0; k < 10; k++) {
	  	int status;
		wait(&status);
		if(WIFEXITED(status)){
		int value = WEXITSTATUS(status);
		} 
  }
  
	  
	execl("ffmpeg", "ffmpeg", "-f concat -i list.txt -c copy output.mp4", NULL);


  return 0;
}