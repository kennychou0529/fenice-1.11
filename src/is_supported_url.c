/* * 
 *  $Id: is_supported_url.c 298 2006-02-28 08:58:07Z shawill $
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

#include <fenice/utils.h>
#include <string.h>

int is_supported_url(char *p)
// Add supported format extensions here
{
	if (strcasecmp(p,".SD")==0) {	
		return 1;
	}
	if (strcasecmp(p,".WAV")==0) {					
		return 1;
	}
	if (strcasecmp(p,".MP3")==0) {	
		return 1;
	}
	if (strcasecmp(p,".GSM")==0) {	
		return 1;
	}
	if (strcasecmp(p,".GSM-FLO")==0) {	
		return 1;
	}
	if (strcasecmp(p,".L16M8K")==0) {	
		return 1;
	}
	if (strcasecmp(p,".26l")==0) {
		return 1;
	}
	if (strcasecmp(p,".mpg")==0) {
		return 1;
	}
	if (strcasecmp(p,".mpeg")==0) {
		return 1;
	}
	if (strcasecmp(p,".m1v")==0) {
		return 1;
	}
	if (strcasecmp(p,".m2v")==0) {
		return 1;
	}
	if (strcasecmp(p,".m4v")==0) {
		return 1;
	}
	if (strcasecmp(p,".mp4")==0) {
		return 1;
	}
	if (strcasecmp(p,".xvid")==0) {
		return 1;
	}
	if (strcasecmp(p,".rtp")==0) {
		return 1;
	}
	return 0;
}

