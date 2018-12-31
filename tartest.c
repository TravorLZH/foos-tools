#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct tar_header {
	char filename[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char type;
	char linkname[100];
	char ustar[6];
	char ustar_ver[2];
	char owner[32];
	char group[32];
	char reserved[183];
} __attribute__((packed));

size_t getsize(const char *in)
{
	size_t size=0;
	size_t i;
	size_t count=1;
	for(i=11;i>0;i--,count*=8)
		size+=((in[i-1]-'0')*count);

	return size;
}

struct tar_header *headers[32];

size_t parse(void* address)
{
	size_t i;
	for(i=0;i<32;i++){
		struct tar_header *header=(struct tar_header*)address;
		if(header->filename[0]=='\0')
			break;
		size_t size=getsize(header->size);
		headers[i]=header;
		address=(char*)address + ((size / 512) + 1) * 512;
		if(size % 512)
			address=(char*)address + 512;
	}
	return i;
}

int main(void)
{
	assert(sizeof(struct tar_header)==512);
	FILE *disk=fopen("../ramdisk2.img","rb");
	if(disk==NULL){
		perror("../ramdisk2.img");
		puts("Trying ./ramdisk2.img instead");
		if((disk=fopen("./ramdisk2.img","rb"))==NULL){
			perror("./ramdisk2.img");
			return 1;
		}
	}
	fseek(disk,0,SEEK_END);
	size_t size=ftell(disk);
	rewind(disk);
	char *buf=malloc(size);
	fread(buf,size,1,disk);
	int len=parse(buf);
	int i;
	for(i=0;i<len;i++){
		printf("%s\t%s@%s\n",headers[i]->filename,headers[i]->owner,
				headers[i]->group);
		if(headers[i]->type=='0' || headers[i]->type=='\0')
			printf("%s",headers[i]+1);
	}
	free(buf);
	fclose(disk);
	return 0;
}
