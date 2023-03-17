# RSA
# Private Key Calculation

See ```er1.c``` file for the code

Let p and q be two prime numbers and e a number.

Let ```n = p * q```

1) I will use ```(e, n)``` as the public key.
2) Calculate the private key d. 

The hexadecimal values of ```p, q```  and e are listed below. It should be noted that although the
```p``` and ```q``` used in this activity are quite large numbers, no
they are big enough to be safe. Obviously we keep them small for simplicity
reasons. In practice, these numbers should be at least 512 bits long
(the one used here is only 128 bits).

•   ```p = F7E75FDC469067FFDC4E847C51F452DF```

•   ```q = E85CED54AF57E53E092113E62F436F4F```

•   ```e = 0D88C3 ```

```e``` results from the formula ```e = (p-1)*(q-1)```

First we create the variables we will need.
```P```, ```q```, ```e``` are in hexadecimal format and we convert them to binary with
```BN_hex2bn()```.

To do operations with the unit, we place it in the variable one
converting it to binary with the command ```BN_dec2bn()``` because we imported it
as a decimal number.

Then we do the operations that will be needed ```p-1```, ```q-1```, ```(p-1)*(q-1)```
using the commands

 •```BN_sub(a,b,c)``` where a stores the operation ```(b-c)```

 •```BN_mul(a,b,c)``` where a stores the operation ```(b*c)```

Finally we use ```BN_mod_inverse(b,a,n,ctx)``` where it calculates ```b```
such that ```(a*b) MOD n = 1``` and we match ```b```, ```a```, ```n```, ```ctx``` with ```d```, ```e```, ```pq```, ```ctx``` which
we found earlier.

At this moment we have found ```d```.

We print it with the function which receives a character pointer
and a BIGNUM pointer.


# Message Encryption

See ```er2.c``` file for the code.

Let ```(e, n)``` be the public key. 

We will encrypt the message ```A top secret!```.

We need to convert this ASCII string to a hexadecimal string
string and then convert the hexadecimal string to
BIGNUM using the hex-to-bn API ```BN_hex2bn()```.

The following python command
can be used to convert a simple ASCII string to a
hexadecimal string.

``` $ python -c ’print("A top secret!".encode("hex"))’```  ```4120746f702073656372657421```


The public keys are listed below (in hexadecimal). We also provide the
private key ```d``` to verify the encryption result.

•```n = DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5```

•```e = 010001``` (this hex value equals to decimal ```65537```)

•```M = A top secret!```

•```d = 74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D```

We know that if we want to encrypt a message ```p``` then we perform the operation
```(p^e) MOD n``` and the result of this is the encrypted message.

In the library this operation is done with the command
 ```BN_mod_exp(res, a, c, n, ctx)``` where it gives us the result ```res = (a^c) MOD n```.

All we need to convert is ```p```. 

```p``` is not expressed as a number, it is in string format. Before rising
to the power must be converted to number form.
This conversion will be done with the python command that was mentioned before.



In the program, i use ```printBN()``` same as the previous examle.

First we create the variables we will need for the exercise.
Then we copy the message ```A top secret!``` in hexadecimal found
above and place it in the variable ```m```.

We do the encryption operation ```res=(m^e) MOD n``` and in ```res``` we have
our cryptogram.

To check if the encryption was done correctly, we use the formula
```res2=(res^d) MOD n``` and the required result
to exist in ```res2``` must be the same as ```m```.


If ```res2``` is the same as ```m``` the encryption was done correctly.

One more action that can be done is to copy the
```res2``` result and run the command below.


```python -c 'print("4120746F702073656372657421".decode("hex"))'```

Running this command must return  ```A top secret!``` that we had
encrypt initialy.

# Message Decryption

See ```er3.c``` file for the code.

Decryption will be performed on the C cipher. At the end it needs to be in a readable form.

```C = 8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F```

We know that the decryption of a
of ciphertext ```c``` is done with the formula ```(c^d) MOD n```.
```d``` is known.
```C``` is known.
```N``` is known.
So all we need to do is make a few conversions
in the ```er2.c``` code.

As before, we initialize the variables that
we need and put values in them, then convert them to
bignum.

We perform the operation ```(c^d) MOD n``` and store the result in
variable ```res```.

The result that has been given to us by this act is the message that
we want to see, but it is represented in hexadecimal. To see it in string format we will execute the command decode for hexadecimal
number, of python as shown below.

```python -c 'print("50617373776F7264256573".decode("hex"))'```

And we have the result ```Password is dees```.

# Digital Signature

See ```er4.c``` file for the code.

The public and private key used in this example are
same as those in the second example (Message Encryption).

We will create a signature for the following message ```M``` = ```I owe you $2000.```.

(We will directly sign this message instead of signing the hash
value)

Then we'll make a small change to the ```M``` message, change ```$2000``` to ```$3000```, and
sign the modified message. Then we will compare the signatures.

Signing a message means encrypting it with the private key.
The private key is the same as before:

```d = 74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D```

The formula to be used is ```(M^d) MOD n```. Where ```d``` is the
private key..
The result of this act is the signature.

To see the difference if the original message will be converted, we will
create a second string, ```I owe you $3000.```.

To enter the strings ```I owe you $2000.``` and ```I owe you $3000.```
we will use the python command to convert from
string in hexadecimal format.

•```python -c 'print("I owe you $2000.".encode("hex"))'```

•```python -c 'print("I owe you $3000.".encode("hex"))'```


In the above code we create the necessary variables that will
we need
The variables ```n```,```d``` are known.
We place in the variables ```m1``` and ```m2```, the decimal representations of
of strings we want to sign.
In ```m1``` is the string ```I owe you $2000.``` in hexadecimal.
In ```m2``` is the string ```I owe you $3000.``` in hexadecimal.


1) We sign the first string with the formula ```(m1^d) MOD n``` and
we store the signature in the ```res``` variable.

2) We sign the second string with the same formula and save
the signature in the ```res2``` variable. 

3) We print the two signatures.

![Capture](https://user-images.githubusercontent.com/103950889/224670822-babd6952-3257-40ee-a96c-21e4d702abf3.PNG)
If everything has been executed correctly, the signatures are different. Therefore
we understand that the message has been changed and is not authentic.

# Signature Verification

See ```er5.c``` file for the code.

```Bob``` receives a message ```M``` = ```Launch a
missile.``` by ```Alice```, signed by her signature ```S```. 
We know that Alice's public key
is ```(e, n)```.

Confirm the signature is Alice's or not. The public key and the
signature (in hexadecimal) are given below:

•```M = Launch a missle.```

•```S = 643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F```

•```e = 010001 (this hex value equals to decimal 65537)```

•```n = AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115```

To find the original message we need to use the formula
```(S^e) MOD n```.

```S``` is Alice's signature and ```e```, ```n``` are known.

The result of this operation gives us the original message in hexadecimal
form.


First we initialize the variables we will need.
 ```n```, ```e``` are known.
We also create the ```res``` variable that the original message will go into, from
the calculation of ```(S^e) MOD n```.

The ```sig``` variable contains the signature given before.
All these variables have been converted to bignum.

We perform the operation ```(S^e) MOD n```. and the result is stored in
variable ```res```.

The image below shows the encrypted message we received (```4C617...```)
![5 1](https://user-images.githubusercontent.com/103950889/224679503-e7e0d285-f867-4def-97b9-8db0a4608009.PNG)

To decrypt the message we need to use the
python decoding command show in the image below
![5 2](https://user-images.githubusercontent.com/103950889/224679945-413a9c39-700f-41f7-8ba1-c0d735dc55cd.PNG)


We notice that by decoding the initial message ```M``` = ```Launch a missle.```
It is different from the message we got ```Launch a missile```

Although the only difference is an ```i```, the message is not the original.

# Libraries Used
•```stdio.h```

•```openssl/bn.h```