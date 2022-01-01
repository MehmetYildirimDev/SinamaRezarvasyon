///Projeyi sinama gişesinde bulunan personel kullanıcakmış gibi tasarladım
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void SifreFonksiyonu(void);///Şifre kontrolu ve ilk şifre oluşturmak için kullanıcağımız fonksiyon


void SeyirciBilgileri(void);///Seyirci bilgilerini alacağımız fonksiyon
typedef struct {///seyirci bilgilerini içeren struct
    int SalonNo;
    int MatineNo;
    int FilmNo;
    int KoltukNo;
    int BiletTuru;
}Seyirciler;
Seyirciler SBilgi[50];
int Ssayac=0;///SBilgi dizisinin indisi olarak kullanmak için tanımladığım sayaç


int KoltukFonksiyonu(void);///Koltuk No vermek için fonksiyon
int KoltukDizisi[50]={0};///Dolu koltukları 1 değerini vermek için boşlara 0 değerini verdim


void Hasilat(int H);///Hasılatı dosyaya yazdıracak fonksiyon
int HasilatToplam=0;///oğrenci veya tam bilete göre artacak sayaç


void SeyirciSayisi(void);///Hangi Salonda kaç kişi olduğunu sayıp bunu dosyaya yazdıran fonksiyon
int Salonbirsayac;
int Salonikisayac;
int Salonucsayac;

void Devam(void);

int main(void)
{
    SifreFonksiyonu();
    SeyirciBilgileri();
    KoltukFonksiyonu();
    Hasilat(HasilatToplam);
    SeyirciSayisi();
    
    return 0;
}

void SifreFonksiyonu(void)
{
    char kullaniciadi[20],kullaniciadi1[20],k_adi[20];
    int sifre,Ksifre,kont1,kont2,sifre1;
    FILE *pSifreD;
    pSifreD=fopen("sifre.txt", "r");///r ile okuyoruz ki eğer yoksa null değeri atasın
    
    if (pSifreD==NULL) {///buraya girerse ilk defs şifre oluşturuyor
        printf("Kullanıcı adı(string) ve şifre(integer) giriniz\nHatırlatma->Belirleyeceğiniz kullanıcı adı ve şifre daha sonra kullanılıcaktır.\n");
        scanf("%s %d",kullaniciadi,&sifre);
        pSifreD=fopen("sifre.txt", "w");
        fprintf(pSifreD,"%s %d",kullaniciadi,sifre);
        system("clear");///DİKKAT
    }
    else///Buraya girerse şifre daha önce belirlenmiş oluyor ve kontrol ediyor
    {
        pSifreD=fopen("sifre.txt", "r");
        printf("Kullanıcı adi ve şifre->");
        scanf("%s %d",k_adi,&Ksifre);///kullanıcının girdiği
        fscanf(pSifreD,"%s %d",kullaniciadi1,&sifre1);///bizim dosyadan okuduğumuz
        kont1 = strcmp(kullaniciadi1, k_adi);
        kont2 =sifre1-Ksifre;
        printf("%d %d \n",kont1,kont2);
        if (kont1 == 0 && kont2 == 0) {
            system("clear");///DİKKAT
            printf("Şifre Başarılı Hoş Geldiniz\n");
        }
        else{
            system("clear");///DİKKAT
            printf("Şifre yanlış\nTekrar deneyiniz\n");
            SifreFonksiyonu();
        }
    }
    fclose(pSifreD);
}

void SeyirciBilgileri(void)
{
    printf("Salon Numarasını Seçiniz\nSeçenekler-> 1.BLUE - 2.RED - 3.GREEN\n");
    scanf("%d",&SBilgi[Ssayac].SalonNo);
    
    switch (SBilgi[Ssayac].SalonNo) {///buradaki switch yapısı ile salonlardaki kişi sayısını sayıyoruz
        case 1:
        {
            Salonbirsayac++;
            break;
        }
        case 2:
        {
            Salonikisayac++;
            break;
        }
        case 3:
        {
            Salonucsayac++;
            break;
        }
        default:
            break;
    }

    printf("Matine Numarası Seçiniz\nSeçenekler-> 1 2 3 4 5\n");
    scanf("%d",&SBilgi[Ssayac].MatineNo);
///İlk başta Her salonda 1 film gösterilecek şekilde düşündüm fakat yönergede film numarası sorulacak denmiş o yüzden ekledim
    printf("Film Numarası Seçiniz\nSeçenekler-> 1 2 3\n");
    scanf("%d",&SBilgi[Ssayac].FilmNo);
    SBilgi[Ssayac].KoltukNo=KoltukFonksiyonu();
    printf("KoltukNo->%d\n",SBilgi[Ssayac].KoltukNo);
    
    printf("Bilet Türünü Seçiniz->\n 1.Öğrenci= 20₺   -   2.Tam = 30₺\n");
    scanf("%d",&SBilgi[0].BiletTuru);
    switch (SBilgi[0].BiletTuru) {///Buradaki switch ile de Hasılatı topluyoruz
        case 1:
        {
            HasilatToplam=HasilatToplam+20;
            break;
        }
        case 2:
        {
            HasilatToplam=HasilatToplam+30;
            break;
        }
        default:
            break;
    }
    Ssayac++;///SBilgi dizisinin indisi olarak kullandığımız sayacı 1 artırıyoruz
    Devam();
}

int KoltukFonksiyonu(void){
    int *pdizi;
    pdizi=KoltukDizisi;
    
    for (int i=0; i<50; i++) {
        if (*(pdizi+i)==0)///Koltuğun boş olduğu sorgulanıyor ve boş ise içeri girip değerini 1 yapıyor
        {
            *(pdizi+i)=1;
            return i+1;
        }
    }
    exit(1);///Burada eğer değeri dönerse 50 kişiyi geçmişiz demektir
}
void Devam(void)
{
    char Cevap;
    printf("Müşteri Eklemeye Devam Etmek İçin 'e' ya da 'E' Basınız\nProgramı Sonlandırmak İçin 'h' ya da 'H' Basınız.\n");
    scanf("%s",&Cevap);
    switch (Cevap) {
        case 'e':
        case 'E':
        {   system("clear");///DİKKAT
            SeyirciBilgileri();
            break;
        }
           
        case 'h':
        case 'H':
        {
            system("clear");///DİKKAT
            break;
        }
        default:{
            break;
        }
    }
}

void Hasilat(int H)///Hasılat bilgileri dosyaya yazılıyor
{
    FILE *pHasilat;
    pHasilat=fopen("Hasilat.txt", "r");
    if (pHasilat==NULL)
    {
        pHasilat=fopen("Hasilat.txt", "w");
        fprintf(pHasilat,"%d₺\n",H);
    }
    else{
        pHasilat=fopen("Hasilat.txt", "a");
        fprintf(pHasilat,"%d₺\n",H);
    }
    
    fclose(pHasilat);
}

void SeyirciSayisi(void)///Salondaki kişi sayısı dosyaya yazılıyor
{
    FILE *pSayi;
    pSayi=fopen("KisiSayisi.txt", "r");
    if (pSayi==NULL) {
        pSayi=fopen("KisiSayisi.txt", "w");
        fprintf(pSayi," BLUE\tRED\tGREEN\n");
        fprintf(pSayi," %d\t%d\t%d\n",Salonbirsayac,Salonikisayac,Salonucsayac);
    }
    else{
        pSayi=fopen("KisiSayisi.txt", "a");
        fprintf(pSayi," %d\t%d\t%d",Salonbirsayac,Salonikisayac,Salonucsayac);
    }
    fclose(pSayi);
}
