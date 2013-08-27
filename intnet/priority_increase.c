/* * 
 *  $Id: priority_increase.c 80 2005-01-25 17:51:15Z federico $
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

#include <string.h>
#include <unistd.h>

#include <fenice/intnet.h>
#include <fenice/mediainfo.h>
#include <fenice/utils.h>

int priority_increase(RTP_session *changing_session)
{
        int priority;
        media_entry req,*list,*p;
	SD_descr *matching_descr;
	
        memset(&req,0,sizeof(req));

        req.description.flags|=MED_PRIORITY;
        enum_media(changing_session->sd_filename, &matching_descr);
	list=matching_descr->me_list;

        priority=changing_session->current_media->description.priority;
	if (priority != 1) {
        	priority -= 1;
        	req.description.priority=priority;
        	p=search_media(&req,list);
        	if (p!=NULL) {
       	       		close(changing_session->current_media->fd);
                	changing_session->current_media->flags &= ~ME_FD;
                	changing_session->current_media=p;
                	return ERR_NOERROR;
        	}
	} else {
		changing_session->MaximumReached = 1;
                return ERR_NOERROR;
        }

	return ERR_GENERIC; // shawill; ERROR or NOERROR? this is the question
}

