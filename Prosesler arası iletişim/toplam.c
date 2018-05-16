
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 
int main()
{
    
 
   
        int sayi; // ust sınır
        int k; // alt sınır
      	printf("alt siniri girin (n) = ");
     	scanf("%d",&sayi);
	    printf("ust siniri girin (k) = ");
     	scanf("%d",&k);
	    int cevap;// her sayıdan gelen (n^3 + n ) sonucu
	    int sondeger = 0; // tüm gelen değerlerin toplanmasından sonra oluşan cevap
        int fd;
        char * myfifo = "/tmp/myfifo";// pipemizi yaratıyoruz.
         mkfifo(myfifo, 0666);
        int array[k-sayi+1]; // elemanlarımızı atmak için toplam eleman sayısı uzunlugunda array
		int i; // for döngüsü değişkeni
		int counter= 1; // değerleri atamak için kullandığım index.
    while (sayi <= k) // alt sınırımız ( sayı ) , üst sınırımız (k) ya eşit olana kadar
			// bu işlem devam edecektir.
    {
        
        
 
        fd = open(myfifo, O_WRONLY); // sadece yazma yetkisi var
        write(fd, &sayi, sizeof(sayi));// fdye sayımızı sayımızın boyutu kadar yazıyoruz
        close(fd); 
        fd = open(myfifo, O_RDONLY); // sadece okuma yetkisi var
		
		
		read(fd, &cevap, sizeof(sayi)); // cevabı sayımızın boyutu kadar okuyoruz

        
         sondeger = sondeger + cevap; // her seferinde gelen sonuç son degere atanıyor 
		// en sonda son değer yazdırılarak sorunun cevabı bulunmuş olunuyor.
	

        sayi++;  // sayımızı her seferinde 1 arttırarak hem sonraki sayıya geçiyoruz
			// hem de sayımızı k sınırına yaklaştırıp döngüyü bitiriyoruz.

	    array[counter-1] = cevap; // index sırasının doğru olması için,her gelen cevap arraye
					// atıldı.
	 for(i = 0; i <counter ; i++){
      printf(" %d +", array[i]);
}
	  printf("\n");
	
	  counter++; // her seferinde counteri arttırarak sonraki değişkenin indexine geçiyoruz.

      close(fd);

    }
      printf("cevap = %d\n", sondeger); // // tüm gelen değerlerin toplanmasından sonra oluşan cevabı yazdırıyoruz.
      return 0;
}
