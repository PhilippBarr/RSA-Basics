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
   BIGNUM *e = BN_new();//given
   BIGNUM *sig = BN_new();
   BIGNUM *res = BN_new();
   BIGNUM *m = BN_new();

   BN_hex2bn(&n,"AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");//public given
   BN_dec2bn(&e,"65537");//public given
   BN_hex2bn(&sig,"643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");//given


   BN_mod_exp(res,sig,e,n,ctx);

   printBN("minima",res);
}
//4C61756E63682061206D697373696C652E  Launch a missile.
