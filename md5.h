#ifndef MD5_H
#define MD5_H
 


void md5_string(const char* str, char digest[33]);
int md5_file(const char* pathname, char digest[33]);


 
#endif