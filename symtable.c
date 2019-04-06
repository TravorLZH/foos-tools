#include "../include/foos/debug.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

FILE *map=NULL;
FILE *out=NULL;

void die(char *label)
{
	perror(label);
	exit(1);
}

int main(int argc,char **argv)
{
	assert(sizeof(struct symtable) == 40);
	struct symtable node;
	memset(&node,0,sizeof(struct symtable));
	node.magic=0xDEADBEEF;
	if(argc<3){
		fprintf(stderr,"Usage: %s [foos.map] [foos.sym]\n",argv[0]);
		return 1;
	}
	map=fopen(argv[1],"r");
	if(map==NULL)
		die(argv[1]);
	out=fopen(argv[2],"wb");
	if(out==NULL)
		die(argv[2]);
	printf("%s -> %s\n",argv[1],argv[2]);
	while(fscanf(map,"%x %s",&node.addr,node.symbol)==2){
		if(!fwrite(&node,sizeof(struct symtable),1,out))
			die("fwrite() failed");
		memset(&node.addr,0,sizeof(struct symtable)-sizeof(uint32_t));
	}
	fclose(map);
	fclose(out);
	return 0;
}
