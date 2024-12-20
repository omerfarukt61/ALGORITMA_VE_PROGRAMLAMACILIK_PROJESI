#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_OYUNCU 25
// Oyuncu verilerini tutan yapı
struct oyuncular {
    char ad[30];//oyuncuların ismi
    char soyad[30];//oyuncuların soyismi
    int macSayisi;//oynadıkları maç sayısı
    int thatalipas;//toplam hatalı pas sayıları
    int tdogrupas;//toplam dogru pas sayıları
};

// fonksiyon olarak atanmıs oyuncu ekleme sistemi
void ekle(struct oyuncular dizi[], int *oyuncuSayisi, char *ad, char *soyad, int hatali, int dogru) {//oyuncu sayisi belirsiz oldugu icin deger atanmadı
    for (int i = 0; i < *oyuncuSayisi; i++) {
        if (strcmp(dizi[i].ad, ad) == 0 && strcmp(dizi[i].soyad, soyad) == 0) {
            // oyuncu bulunursa veriler güncellenir
            dizi[i].macSayisi++;
            dizi[i].thatalipas += hatali;
            dizi[i].tdogrupas += dogru;
            return;
        }
    }
    // oyuncu sistemde yoksa ekleme
    strcpy(dizi[*oyuncuSayisi].ad, ad);
    strcpy(dizi[*oyuncuSayisi].soyad, soyad);
    dizi[*oyuncuSayisi].macSayisi = 1;
    dizi[*oyuncuSayisi].thatalipas = hatali;
    dizi[*oyuncuSayisi].tdogrupas = dogru;
    (*oyuncuSayisi)++;
}

// toplam txt dosyasına kaydetme fonksiyonu
void yazdir(struct oyuncular dizi[], int oyuncuSayisi) {
     oyuncuSayisi=20;
    FILE *cikis = fopen("toplam.txt", "w");
    if (cikis == NULL) {
        printf("toplam.txt dosyası oluşturulamadı.\n");
        return;
    }
    fprintf(cikis,"|oyuncu ismi|\t |oynanan mac|\t |hatali pas| \t |dogru pas|\n");//her parametre arasında bir tab kadar boşluk bırakarak yazdır
    for (int i = 0; i < oyuncuSayisi; i++) {
        fprintf(cikis, "%s %s\t\t\t %d\t\t\t\t %d\t\t\t %d\n", dizi[i].ad, dizi[i].soyad, dizi[i].macSayisi,
                dizi[i].thatalipas, dizi[i].tdogrupas);//sıralı bir şekilde olması için aralarda tab kadar boşluk bulundurur
    }
    fclose(cikis);
}

int main() {
    struct oyuncular dizi[MAX_OYUNCU];
    int oyuncuSayisi = 0;
    char ad[30], soyad[30];
    int hatali, dogru;

    // Dosyayı aç ve verileri oku
    FILE *dosya = fopen("paslar.txt", "r");
    if (dosya == NULL) {
        printf("paslar.txt dosyası bulunamadı.\n");
        return 1;
    }
    while (fscanf(dosya, "%s %s %d %d", ad, soyad, &hatali, &dogru) != EOF) {
        ekle(dizi, &oyuncuSayisi, ad, soyad, hatali, dogru);//dosyadan alınan hatalı ve dogru pas sayılarını işleme göndertme
    }
    fclose(dosya);

    // alınan verileri  toplam.txt dosyasına girdiren fonksiyona yönlendirme
    yazdir(dizi, oyuncuSayisi);
    return 0;
}