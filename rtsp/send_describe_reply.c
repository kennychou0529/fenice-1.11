/* * 
 *  $Id: send_describe_reply.c 139 2005-05-12 14:55:17Z federico $
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
#include <stdlib.h>

#include <config.h>
#include <fenice/rtsp.h>
#include <fenice/utils.h>
#include <fenice/fnc_log.h>

int send_describe_reply(RTSP_buffer * rtsp, char *object, description_format descr_format, char *descr)
{
	char *r;		/* get reply message buffer pointer */
	char *mb;		/* message body buffer pointer */
	int mb_len;

		
	/* allocate buffer */
	mb_len = 2048;
	mb = malloc(mb_len);
	r = malloc(mb_len + 1512);
	if (!r || !mb) {
		fnc_log(FNC_LOG_ERR,"send_describe_reply(): unable to allocate memory\n");
		send_reply(500, 0, rtsp);	/* internal server error */
		if (r) {
			free(r);
		}
		if (mb) {
			free(mb);
		}
		return ERR_ALLOC;
	}

	/*describe*/
	sprintf(r, "%s %d %s"RTSP_EL"CSeq: %d"RTSP_EL"Server: %s/%s"RTSP_EL, RTSP_VER, 200, get_stat(200), rtsp->rtsp_cseq, PACKAGE, VERSION);
	add_time_stamp(r, 0);
	switch (descr_format) {
		// Add new formats here
		case df_SDP_format:{
			strcat(r, "Content-Type: application/sdp"RTSP_EL);
		break;
		}
	}
	sprintf(r + strlen(r), "Content-Base: rtsp://%s/%s/"RTSP_EL, prefs_get_hostname(), object);
	sprintf(r + strlen(r), "Content-Length: %d"RTSP_EL, strlen(descr));
	// end of message
	strcat(r, RTSP_EL);

	// concatenate description
	strcat(r, descr);
	bwrite(r, (unsigned short) strlen(r), rtsp);

	free(mb);
	free(r);
	
	fnc_log(FNC_LOG_CLIENT,"200 %d %s ",strlen(descr),object);
	
	return ERR_NOERROR;
}
