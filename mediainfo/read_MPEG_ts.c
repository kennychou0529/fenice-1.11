/* * 
 *  $Id$
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
#include <unistd.h>
#include <string.h>
#if HAVE_ALLOCA_H
#include <alloca.h>
#endif

#include <fenice/types.h>
#include <fenice/utils.h>
#include <fenice/mediainfo.h>
#include <fenice/mpeg_ts.h>

int read_MPEG_ts(media_entry *me, uint8 *data_slot,uint32 *data_size, double *mtime, int *recallme, uint8 *marker)
{
	int ret;
	uint32 num_bytes;
	uint8 *data;
	
	*marker=*recallme=0;
	num_bytes = ((me->description).byte_per_pckt/188)*188;
#if HAVE_ALLOCA
        data=(unsigned char *)alloca(num_bytes+4);
#else
        data=(unsigned char *)calloc(1,num_bytes+4);
#endif
        if (data==NULL)
               return ERR_ALLOC;

	if (!(me->flags & ME_FD)) {
		if ( (ret=mediaopen(me)) < 0 ){
#if !HAVE_ALLOCA
			free(data);
#endif	
			return ret;
		}
		*data_size=0;
        }  
	
	*data_size=read(me->fd,data,num_bytes);
	if(*data_size<=0){
#if !HAVE_ALLOCA
		free(data);
#endif	

		return ERR_EOF;
	}
        memcpy(data_slot, data, *data_size); 
#if !HAVE_ALLOCA
	free(data);
#endif
	
	return ERR_NOERROR;
}

