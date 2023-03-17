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

   BIGNUM *p = BN_new();
   BIGNUM *q = BN_new();
   BIGNUM *e = BN_new();
   BIGNUM *one = BN_new();
   BIGNUM *a = BN_new();
   BIGNUM *b = BN_new();
   BIGNUM *d = BN_new();
   BIGNUM *pq = BN_new();

   BN_hex2bn(&p,"F7E75FDC469067FFDC4E847C51F452DF");
   BN_hex2bn(&q,"E85CED54AF57E53E092113E62F436F4F");
   BN_hex2bn(&e,"0D88C3");
   BN_dec2bn(&one,"1");

   BN_sub(a,p,one); //p-1
   BN_sub(b,q,one); // q-1
   BN_mul(pq,a,b,ctx); //(p-1)*(q-1)

   BN_mod_inverse(d,e,pq,ctx);

   printBN("the private key is ",d);
}
