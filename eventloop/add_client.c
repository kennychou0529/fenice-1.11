/* * 
 *  $Id: add_client.c 176 2005-06-28 14:47:59Z shawill $
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

#include <stdio.h>
#include <string.h>

#include <fenice/eventloop.h>
#include <fenice/socket.h>
#include <fenice/rtsp.h>
#include <fenice/fnc_log.h>

void add_client(RTSP_buffer **rtsp_list,tsocket fd)
{
	RTSP_buffer *p=NULL,*pp=NULL;
	// Add a client
	if (*rtsp_list==NULL) 
	{
		if ( !(*rtsp_list=(RTSP_buffer*)calloc(1,sizeof(RTSP_buffer)) ) ) 
		{
			fnc_log(FNC_LOG_FATAL,"Could not alloc memory\n\n");
			return;
		}
		p=*rtsp_list;
	}
	else {								
		for (p=*rtsp_list; p!=NULL; p=p->next) {					
			pp=p;
		}
		if (pp!=NULL) {
			if ( !(pp->next=(RTSP_buffer *)calloc(1,sizeof(RTSP_buffer)) ) ) {
				fnc_log(FNC_LOG_FATAL,"Could not alloc memory\n");
				return;
			}
			p=pp->next;
			p->next=NULL;
		}
	}
	RTSP_initserver(p,fd);
	fnc_log(FNC_LOG_INFO,"Incoming RTSP connection accepted on socket: %d\n",p->fd);
}

