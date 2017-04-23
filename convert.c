#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{

	// get the size of data.txt
	struct stat sb;
	int fd, N;
	fd = open("data.txt", O_RDWR);
	fstat(fd, &sb);
	N = sb.st_size;
	
	char *data, *key;
	int index=0;
	// add '\0'	
	data = malloc( (N/4096)*4092 * sizeof(char));	
	key = malloc( (N/4096)*5 * sizeof(char));	

	//open file
	FILE *Rptr, *Wptr;
	Rptr = fopen("data.txt", "r");
	Wptr = fopen("new_data.txt", "w");
	
	//read the data to data array
	while( fscanf(Rptr, "%4s%4092s", key+index*5, data+index*4092) != EOF)
	{
		key[index*5+4] = '\0';
		data[index*4092+4091] = '\0';
		//printf("%s%s\n", key+index*5, data+index*4092);
		//printf("???: %d\n", *(data+index*4092+4090));
		index++;
	}

	int i;
	for(i=0;i<index;i++)
	{
		fprintf(Wptr, "%s", key+i*5);
	}
	for(i=0;i<index;i++)
	{
		fprintf(Wptr, "%s\n", data+i*4092);
	}

	//free, close
	free(data);
	fclose(Rptr);	
	fclose(Wptr);	
	close(fd);
}
