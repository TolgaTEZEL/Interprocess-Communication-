#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
      int sayi;
     
      read(3, &sayi, sizeof(sayi)); //  sayimizi okuyoruz
      int sonuc= sayi*sayi*sayi;  // küpünü alarak sonucu bulup 
      
      write(4, &sonuc, sizeof(sonuc)); // write ile bulduğumuz sonucu yolluyoruz.

    return 0;
}

