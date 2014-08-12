#ifndef _COMM_H_
#define _COMM_H

#define FREE(p) if(p) {\
			free(p);\
		}


#define Q_LOCK(q)           	pthread_mutex_lock(q)
#define Q_UNLOCK(q)         	pthread_mutex_unlock(q)

#define G_LOCK(q)           	pthread_mutex_lock(q)
#define G_UNLOCK(q)         	pthread_mutex_unlock(q)

#endif
