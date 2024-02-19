#ifndef SHA_H
#define SHA_H


//一次循环过程，str为填充后的数据或是数据中的一部分 
void round1(unsigned char str[64],unsigned int h[5]);

//sha-1算法 
void sha1(unsigned char*input,long long len,unsigned char*output);




#endif