#include<stdio.h>
#include<openssl/bn.h>

#define NBITS 256

void printBN(char *msg,BIGNUM *a)
{
   char *number_str=BN_bn2hex(a);
   printf("%s %s \n",msg,number_str);
   OPENSSL_free(number_str);
}

int main()
{
   BN_CTX *ctx = BN_CTX_new();

   BIGNUM *e = BN_new();//given
   BIGNUM *n = BN_new();//given

   BIGNUM *c = BN_new();//given
   BIGNUM *d = BN_new();//given
   BIGNUM *res=BN_new();//
   BIGNUM *res2=BN_new();

   BN_hex2bn(&n,"DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");//public
   BN_dec2bn(&e,"65537");//public

   BN_hex2bn(&c,"8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F");//A top secret!
   BN_hex2bn(&d,"74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");//private


   BN_mod_exp(res,c,d,n,ctx);// (m^e) mod n


   printBN("decode",res);
 }
