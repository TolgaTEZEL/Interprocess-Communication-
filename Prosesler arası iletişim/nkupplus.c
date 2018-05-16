#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[],char** arg)
{
      int sayi;
      
      read(3, &sayi, sizeof(sayi)); // sayiyi okuyoruz ( n^3) 
      int sonuc2= sayi+ cbrt(sayi); // ilk sonucumuz n^3 idi. bu da 2. sonucumuz.
				// cbrt fonksiyonu verilen sayının küp kökünü bulmaya yarıyor.
      			        // sayımız(n^3) ile n yi toplayıp sonuc2ye atıyoruz.
	printf("%g^3 + %g = %d \n",cbrt(sayi),cbrt(sayi),sonuc2);
      write(4, &sonuc2, sizeof(sonuc2)); // sonucumuzu pipe yazıyoruz
	

    return 0;
}

