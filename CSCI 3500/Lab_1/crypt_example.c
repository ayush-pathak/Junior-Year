//A simple example demonstrating ecb_crypt()


#include <stdio.h>
#include <rpc/des_crypt.h>

int main () {

	char buffer[] = "operating systems is fun";
//	char buffer[] = "123412341234123412341234";
	int bufSize = 24;
	char key[] = "abcd1234";

	printf("Before setparity: %s\n", key);
	des_setparity(key);
	printf("After setparity %s\n", key);

	printf("Before encrypt:\n");
	printf("%s\n", buffer);	

	ecb_crypt( key, buffer, bufSize, DES_ENCRYPT); 

	printf("After encrypt:\n");
	printf("%s\n", buffer);	

	ecb_crypt( key, buffer, bufSize, DES_DECRYPT); 

	printf("After decrypt:\n");
	printf("%s\n", buffer);	


	return 0;
}
