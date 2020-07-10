#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
typedef int(*hook)(int,int);
unsigned char bin_code[] = {
	0x55,
	0x48,0x89,0xe5,
	0x89,0x7d,0xfc,
	0x89,0x75,0xf8,
	0x8b,0x55,0xfc,
	0x8b,0x45,0xf8,
	0x01,0xd0,
	0x5d,
	0xc3
};

int main(void)
{
	hook	func = NULL;
	int ret = 0;
	void *buf = mmap(NULL,sizeof(bin_code),PROT_WRITE | PROT_EXEC,MAP_ANON | MAP_PRIVATE,-1,0);
	
	if(!buf){
		printf("%s:%d\n",__func__,__LINE__);
		return 0;
	}
	
	memcpy(buf,bin_code,sizeof(bin_code));
	func = (hook)buf;
	ret = func(1,2);
	printf("ret = %d\n",ret);
	munmap(buf,sizeof(bin_code));

	return 0;
}
