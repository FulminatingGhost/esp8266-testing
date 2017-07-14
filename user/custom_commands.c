//Copyright 2015 <>< Charles Lohr, see LICENSE file.

#include <commonservices.h>
#include "esp82xxutil.h"

int ICACHE_FLASH_ATTR CustomCommand(char * buffer, int retsize, char *pusrdata, unsigned short len) {
	char * buffend = buffer;

	switch( pusrdata[1] ) {
		// Custom command test
		case 'C': case 'c':
			buffend += ets_sprintf( buffend, "CC" );
        	printf("CC");
			return buffend-buffer;
		break;

		// Echo to UART
		case 'E': case 'e':
			if( retsize <= len ) return -1;
			ets_memcpy( buffend, &(pusrdata[2]), len-2 );
			buffend[len-2] = '\0';
			printf( "%s\n", buffend );
			return len-2;
		break;
	        case 'm': case 'M': //Oscilloscope
		{
			int i;
                	buffend += ets_sprintf( buffend, "CM\t" );
			uint8_t rssi = (uint8_t)abs(wifi_station_get_rssi());
                        *(buffend++) = tohex1( rssi>>4 );
                        *(buffend++) = tohex1( rssi&0x0f );
        		return buffend-buffer;
		}
		break;
	}

	return -1;
}
