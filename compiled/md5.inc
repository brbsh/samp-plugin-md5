/*

			     MD5 include
			    BJIADOKC & Co.
	Remove this copyright, if you want to be a superman!
*/





#if defined _md5_included
	#endinput
#endif

#define _md5_included





#pragma tabsize 8




native md5(dest[], source[], size = sizeof dest);
native md5_hmac(dest[], source[], hmac[], size = sizeof dest);
native md5_file(dest[], filename[], size = sizeof dest);




#pragma tabsize 4
