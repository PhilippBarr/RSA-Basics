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

   BIGNUM *n = BN_new();//given
   BIGNUM *m1 = BN_new();// A top secret!
   BIGNUM *m2 = BN_new();//
   BIGNUM *d = BN_new();//given
   BIGNUM *res=BN_new();//
   BIGNUM *res2=BN_new();

   BN_hex2bn(&n,"DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");//public

   BN_hex2bn(&m1,"49206f776520796f752024323030302e");//owe you 2000
   BN_hex2bn(&m2,"49206f776520796f752024333030302e");//owe you 3000

   BN_hex2bn(&d,"74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");//private


   BN_mod_exp(res,m1,d,n,ctx);
   BN_mod_exp(res2,m2,d,n,ctx);

   printBN("sig1",res);
   printBN("sig2",res2);
}
