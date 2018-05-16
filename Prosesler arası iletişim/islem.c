#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{

    int fd1;

    char * myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);
 
   
    int sayi; // n alt sınırımızın ismi 

    int pipefd[2]; //pipemiz
    int pid; // 1.fork
    int pid1;//2.fork
    int enSonDeger; // her işlemin en sonunda gelen sayı ( n^3 + n in sonucu )

	
      int nkupExecv;  // nkup programı için execv degiskeni
      int nkupplusExecv; // nplusplus prog2
      int sonuc;// ( n^3 sonucu)
      int sonuc2; // ( n^3 + n ) sonucu
      if (pipe(pipefd) < 0) { // pipenin olusup olusmadıgını kontrol ediyoruz.
        perror("pipe");
        exit(1); // hata durumunda çıkış
      }


          
	while (1) {

 	  fd1 = open(myfifo,O_RDONLY); // sadece okuma yetkisi vererek fd1i açıyoruz
	  read(fd1, &sayi ,sizeof(sayi)); // sayımızı fd1in içine yazıyoruz.
          close(fd1);
        
      
          pid = fork(); // ilk forkumuzu oluşturuyoruz.
      

      if (pid == 0) { // child proses olup olmadığını kontrol ediyoruz.
          
          write(pipefd[1], &sayi, sizeof(sayi));// sayımızı pipemize yazıyoruz.
          
          nkupExecv = execv("nkup", NULL);// execv yardımıyla nkup isimli programa ulaştık
         
          perror("");// hata oluşması durumunda 
          close(pipefd[1]); // pipemizi kapatıyoruz.
       
      } else {
          
         wait(&nkupExecv);// işlemin/programın  bitmesini bekliyoruz.
         read(pipefd[0], &sonuc, sizeof(sonuc));   // nkupden gelen sonucumuzu(n^3) okuyoruz.
	 sonuc2= sonuc; // nkupplusda kullanmak için sonucu = sonuc2ye esitliyoruz.

        }

         pid1= fork();// 2. forkumuzu oluşturuyoruz.

	if (pid1 == 0) { // child proses olup olmadığını kontrol ediyoruz.
          
          write(pipefd[1], &sonuc2, sizeof(sonuc2));// sayımızı pipemize yazıyoruz.sonuc2=n^3 
           
          nkupplusExecv = execv("nkupplus", NULL);// execv yardımıyla nkupplus isimli programa ulaştık
           
          perror("");// hata oluşması durumunda 
          close(pipefd[1]);// pipemizi kapatıyoruz.
      } else {
          
         wait(&nkupplusExecv);// işlemin/programın  bitmesini bekliyoruz.

         read(pipefd[0], &sonuc2, sizeof(sonuc2));//gelen sonuc2 sonucunu okuyoruz ( n^3 + n )
	 	
         enSonDeger = sonuc2;// sonuc2mizi enSonDeger isimli en sondaki değer olan değişkenimize eşitliyoruz.
		
        }
	

        fd1 = open(myfifo,O_WRONLY);	// sadece yazma yetkisi veriyoruz
	write(fd1, &enSonDeger, sizeof(int)); // en son değerimizi yazıyoruz ( n^3 + n)
        close(fd1); // fd1 i kapatıyoruz.
	}
      
      return 0;
  }

