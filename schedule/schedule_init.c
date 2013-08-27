/* * 
 *  $Id: schedule_init.c 151 2005-05-20 16:19:09Z federico $
 *  
 *  This file is part of Fenice
 *
 *  Fenice -- Open Media Server
 *
 *  Copyright (C) 2004 by
 *  	
 *	- Giampaolo Mancini	<giampaolo.mancini@polito.it>
 *	- Francesco Varano	<francesco.varano@polito.it>
 *	- Marco Penno		<marco.penno@polito.it>
 *	- Federico Ridolfo	<federico.ridolfo@polito.it>
 *	- Eugenio Menegatti 	<m.eu@libero.it>
 *	- Stefano Cau
 *	- Giuliano Emma
 *	- Stefano Oldrini
 * 
 *  Fenice is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Fenice is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Fenice; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *  
 * */

#include <fenice/schedule.h>
#include <fenice/rtp.h>
#include <time.h>
#include <fenice/utils.h>
#ifdef THREADED
#include <pthread.h>
#endif


schedule_list sched[ONE_FORK_MAX_CONNECTION];

int schedule_init()
{	
	int i;
	#ifdef THREADED
	pthread_t thread;
	#endif	
	#ifdef SIGNALED
	struct itimerval value;
	#endif
	#ifdef SELECTED
	pthread_t t;
	#endif
	
	for (i=0; i<ONE_FORK_MAX_CONNECTION; ++i) {
		sched[i].rtp_session=NULL;
		sched[i].play_action=NULL;		
		sched[i].valid=0;
	}
	#ifdef SIGNALED
	if (signal(SIGALRM,schedule_do)==SIG_ERR) {
		return ERR_FATAL;	
	}	
	value.it_interval.tv_sec=0;
	value.it_interval.tv_usec=5000;
	value.it_value.tv_sec=0;
	value.it_value.tv_usec=value.it_interval.tv_usec;	
	setitimer(ITIMER_REAL,&value,0);
	#endif
	#ifdef THREADED
	pthread_create(&thread,NULL,schedule_do,0);
	#endif
	#ifdef SELECTED
	pthread_create(&thread,NULL,schedule_do,0);
	#endif
	return ERR_NOERROR;
}

