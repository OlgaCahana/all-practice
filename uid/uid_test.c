#include <stdio.h> /* pritnf */

#include "uid.h"

void foo(void)
{
	uid_ty uid3 = SimpleUIDCreate();
	printf("Called func UID: %d-%ld-%lu\n", uid3.pid, uid3.time, uid3.counter);
}

int main (void)
{
	uid_ty uid1 = SimpleUIDCreate();
	uid_ty uid2 = SimpleUIDCreate();	
	uid_ty uid4 = SimpleUIDCreate();
		
	printf("The UID is %d-%ld-%lu\n", uid1.pid, uid1.time, uid1.counter);
	printf("The UID is %d-%ld-%lu\n", uid2.pid, uid2.time, uid2.counter);
	foo();
	printf("The UID is %d-%ld-%lu\n", uid4.pid, uid4.time, uid4.counter);
	
	SimpleUIDCmp(uid1, BadUID) ?
		printf("uid1 is bad UID\n") :
		printf("uid1 is a valid ID\n");
		
		SimpleUIDCmp(uid1, uid1) ?
		printf("uid1 is the same UID\n") :
		printf("uid1 is a not the same UID\n");
	
	return 0;
}
