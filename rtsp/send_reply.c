/* * 
 *  $Id: send_reply.c 139 2005-05-12 14:55:17Z federico $
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

#include <fenice/rtsp.h>
#include <fenice/utils.h>
#include <fenice/fnc_log.h>

int send_reply(int err, char *addon, RTSP_buffer * rtsp)
{
	unsigned int len;
	char *b;
	char *p;
	int res;
	char method[32];
	char object[256];
	char ver[32];


	if (addon != NULL) {
		len = 256 + strlen(addon);
	} else {
		len = 256;
	}

	b = (char *) malloc(len);
	if (b == NULL) {
		fnc_log(FNC_LOG_ERR,"send_reply(): memory allocation error.\n");
		return ERR_ALLOC;
	}
	memset(b, 0, sizeof(b));
	sprintf(b, "%s %d %s"RTSP_EL"CSeq: %d"RTSP_EL, RTSP_VER, err, get_stat(err), rtsp->rtsp_cseq);
	//---patch coerenza con rfc in caso di errore
	// strcat(b, "\r\n");
	strcat(b, RTSP_EL);

	res = bwrite(b, (unsigned short) strlen(b), rtsp);
	free(b);
	
	sscanf(rtsp->in_buffer, " %31s %255s %31s ", method, object, ver);
	fnc_log(FNC_LOG_ERR,"%s %s %s %d - - ", method, object, ver, err);
	if ((p=strstr(rtsp->in_buffer, HDR_USER_AGENT))!=NULL) {
		char cut[strlen(p)];
		strcpy(cut,p);
		cut[strlen(cut)-1]='\0';
		fnc_log(FNC_LOG_CLIENT,"%s",cut);
	}
	
	return res;
}
