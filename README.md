# Vigenere Cipher Decryption

Compile: g++ -std=c++11 Vigenere.cpp

Run: ./a.out

The ciphertext is in **vig2.txt**

## Decryption Process:

First, scan through the ciphertext and convert all letters to uppercases so that the code would work in a certain range. Then, use the Index of Coincidence method to find the most likely key length. To determine the key, we need to try all possible combinations of Caesar cipher and for each result, compute the frequencies of letters and their correlation to frequencies of letters in the English alphabet.

The Caesar cipher which gives the highest correlation is probably the Caesar cipher used in Vigenère cipher. Series of such Caesar ciphers gives us the Vigenère cipher key.

## Results

Key: NOES

Plaintext: UPON THIS BASIS I AM GOING TO SHOW YOU HOW A BUNCH OF BRIGHT YOUNG FOLKS DID FIND A CHAMPION A MAN WITH BOYS AND GIRLS OF HIS OWN A MAN OF SO DOMINATING AND HAPPY INDIVIDUALITY THAT YOUTH IS DRAWN TO HIM AS IS A FLY TO A SUGAR BOWL IT IS A STORY ABOUT A SMALL TOWN IT IS NOT A GOSSIPY YARN NOR IS IT A DRY MONOTONOUS ACCOUNT FULL OF SUCH CUSTOMARY FILL INS AS ROMANTIC MOONLIGHT CASTING MURKY SHADOWS DOWN A LONG WINDING COUNTRY ROAD IT WASNT THAT HARD WAS IT

(the output plaintext is not spaced)
