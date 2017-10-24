#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// This code just work with capital case massage.
// However you can do a pull request with a uppercase function.

// Convert decimal to character from ASCII table
char chr(int dec){
  char character = dec;
  return character;
};

// Convert character to decimal from ASCII table
int ord(char character){
  int dec = (int)character;
  return dec;
};

// Return a length of a char array
int len(char* string){
  int i = 0, length = 0;
  while (string[i] != '\0'){
    length = length + 1;
    i = i + 1;
  }
  return length;
};

// Return the module
int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

// Return a random value between 0 and max_number
int randint(int max_number){
  return (rand() % max_number);
};

// Return a random value between min_number and max_number
int randrange(int min_number, int max_number){
  return (rand() % (max_number + 1 - min_number) + min_number);
};

// Return a random string size of length
char* getKey(int length){
  int i, value = 0;
  char* key = malloc(length);
  for (i = 0; i < length; i++){
    value = randrange(65, 91);
    if (value == 91) {
      key[i] = ' ';
    } else {
      key[i] = chr(value);
    };
  };
  return key;
};

// One-time pad encrypt
char* encrypt(char* message, char* key){
  int i;
  char* cipher_msg = malloc(sizeof(message));
  for (i = 0; i < len(message); i++){
    if (key[i] == ' ')
      cipher_msg[i] = chr(((ord(message[i]) - 65 + (91 - 65)) % 26) + 65);
    else if (message[i] == ' ') {
      cipher_msg[i] = chr(mod((91 - 65 + (ord(key[i]) - 65)), 26) + 65);
    }
    else
      cipher_msg[i] = chr(mod((ord(message[i]) - 65 + (ord(key[i]) - 65)), 26) + 65);
  };
  return(cipher_msg);
};

char* decrypt(char* cipher_msg, char* key){
  int i;
  char* decrypted_msg = malloc(sizeof(cipher_msg));
  for (i = 0; i < len(cipher_msg); i++){
    if (key[i] == ' ')
      decrypted_msg[i] = cipher_msg[i];
    else if (cipher_msg[i] == key[i])
      decrypted_msg[i] = ' ';
    else
      decrypted_msg[i] = chr(mod((ord(cipher_msg[i]) - 65 - (ord(key[i]) - 65)), 26) + 65);
  };
  return decrypted_msg;
};

int main(){
  srand(time(NULL));
  char* message = "HELLO WORLD";
  char* key = getKey(len(message));
  char* cipher_msg;
  char* decrypted_msg;
  printf("Message: %s\n", message);
  printf("Key:\t %s\n", key);
  cipher_msg = encrypt(message, key);
  printf("Encrypt message: %s\n", cipher_msg);
  decrypted_msg = decrypt(cipher_msg, key);
  printf("Decrypted message: %s\n", decrypted_msg);
	return 0;
}
