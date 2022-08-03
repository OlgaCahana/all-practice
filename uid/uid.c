#include <stdio.h> /* pritnf */

#include <time.h> /* time, time_t, size_t */
#include <unistd.h> /* pid_t, getpid */
#include <stdio.h> /* perror */

#include "uid.h"

const uid_ty BadUID = {0, -1, 0};

uid_ty SimpleUIDCreate(void)
{
	static size_t counter = 0;
	
	uid_ty uid;
	uid.pid = getpid();
	uid.time = time(NULL);
	if (uid.time == (time_t)-1)
	{
		perror("Error:");
		return BadUID;
	}

	++counter; /* incremented only for successful id create */
	uid.counter = counter;
	
	return uid;
}

int SimpleUIDCmp(uid_ty uid1, uid_ty uid2)
{
	return (uid1.pid == uid2.pid && 
			uid1.time == uid2.time &&
	 		uid1.counter == uid2.counter);
}
