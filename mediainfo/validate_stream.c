/* * 
 *  $Id: validate_stream.c 338 2006-04-27 16:45:52Z shawill $
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

#define GLOBAL_RTP_DEFS

#include <stdio.h>
#include <string.h>

#include <fenice/utils.h>
#include <fenice/mediainfo.h>
#include <fenice/rtpptdefs.h>
#include <fenice/rtsp.h>
#include <fenice/multicast.h>


int validate_stream(media_entry *p, SD_descr ** sd_descr)
{

        RTP_static_payload pt_info;
	char object[255], server[255];
	unsigned short port;
	int res;
	
        if (!(p->flags & ME_FILENAME)) {
                return ERR_PARSE;
        }       
        if (!(p->description.flags & MED_PAYLOAD_TYPE)) {
                return ERR_PARSE;
        }       
        if (!(p->description.flags & MED_PRIORITY)) {
                return ERR_PARSE;
        }       
	
	/*
	 *- validate multicast
	 *- validate twin
	 * */
	if(parse_url((*sd_descr)->twin,server, sizeof(server), &port, object, sizeof(object)))
		(*sd_descr)->flags &= ~SD_FL_TWIN;

	if(!is_valid_multicast_address((*sd_descr)->multicast))
		strcpy((*sd_descr)->multicast,DEFAULT_MULTICAST_ADDRESS);
	
	if (p->description.payload_type>=96) {
		// Basic information needed for a dynamic payload type (96-127)
		if (!(p->description.flags & MED_ENCODING_NAME)) {
			return ERR_PARSE;
		}
		if (!(p->description.flags & MED_CLOCK_RATE)) {
			return ERR_PARSE;
		}
	} else {
		// Set payload type for well-kwnown encodings and some default configurations if i know them
		// see include/fenice/rtpptdefs.h
		pt_info=RTP_payload[p->description.payload_type];
		if (!(p->description.flags & MED_ENCODING_NAME) || \
			(strcmp(p->description.encoding_name, "RTP_SHM")))
			strcpy(p->description.encoding_name,pt_info.EncName);
		p->description.clock_rate=pt_info.ClockRate;
		p->description.audio_channels=pt_info.Channels;
		p->description.bit_per_sample=pt_info.BitPerSample;
		p->description.coding_type=pt_info.Type;
		p->description.pkt_len=pt_info.PktLen;
		p->description.flags|=MED_ENCODING_NAME;
		p->description.flags|=MED_CLOCK_RATE;
		p->description.flags|=MED_AUDIO_CHANNELS;
		p->description.flags|=MED_BIT_PER_SAMPLE;
		p->description.flags|=MED_CODING_TYPE;
		// p->description.flags|=MED_PKT_LEN;
	}
	res=register_media(p);
	if(res==ERR_NOERROR)
		return p->media_handler->load_media(p);
	else
		return res;
}


