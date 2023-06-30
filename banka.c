#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int hesapNo;
    double bakiye;
} User;

User users[100];

int kullaniciSayisi = 0;

void saveDataToFile() {
    FILE* file = fopen("kullanicilar.txt", "w");
    if (file == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    int i;
    for (i = 0; i < kullaniciSayisi; i++) {
        fprintf(file, "%s %d %.2lf\n", users[i].name, users[i].hesapNo, users[i].bakiye);
    }

    fclose(file);
    printf("Veriler dosyaya kaydedildi.\n");
}

void loadDataFromFile() {
    FILE* file = fopen("kullanicilar.txt", "r");
    if (file == NULL) {
        printf("Dosya bulunamadi.\n");
        return;
    }

    while (!feof(file)) {
        User yeniKullanici;
        int scannedItems = fscanf(file, "%s %d %lf", yeniKullanici.name, &yeniKullanici.hesapNo, &yeniKullanici.bakiye);
        if (scannedItems == 3) {
            users[kullaniciSayisi] = yeniKullanici;
            kullaniciSayisi++;
        }
    }

    fclose(file);
    printf("Veriler dosyadan yuklendi.\n");
}

void createUser() {
    if (kullaniciSayisi >= 100) {
        printf("Maksimum kullanici sayisina ulasildi.\n");
        return;
    }

    User yeniKullanici;
    printf("Kullanici adi: ");
    scanf("%s", yeniKullanici.name);
    printf("Hesap numarasi: ");
    scanf("%d", &yeniKullanici.hesapNo);
    printf("Baslangic bakiyesi: ");
    scanf("%lf", &yeniKullanici.bakiye);
    printf("Yeni kullanici olusturuldu.\n");

    users[kullaniciSayisi] = yeniKullanici;
    kullaniciSayisi++;

    saveDataToFile();
}

void updateUser() {
    int hesapNo;
    printf("Hesap numaranizi giriniz: ");
    scanf("%d", &hesapNo);

    int i;
    for (i = 0; i < kullaniciSayisi; i++) {
        if (users[i].hesapNo == hesapNo) {
            printf("Yeni kullanici adi: ");
            scanf("%s", users[i].name);
            printf("Yeni baslangic bakiyesi: ");
            scanf("%lf", &users[i].bakiye);
            printf("Kullanici guncellendi.\n");

            saveDataToFile();
            return;
        }
    }

    printf("Hesap numarasi bulunamadi.\n");
}

void deleteUser() {
    int hesapNo;
    printf("Hesap numaranizi girin: ");
    scanf("%d", &hesapNo);

    int i;
    for (i = 0; i < kullaniciSayisi; i++) {
        if (users[i].hesapNo == hesapNo) {
            int j;
            for (j = i; j < kullaniciSayisi - 1; j++) {
                users[j] = users[j + 1];
            }
            kullaniciSayisi--;
            printf("Kullanici silindi.\n");

            saveDataToFile();
            return;
        }
    }

    printf("Hesap numarasi bulunamadi.\n");
}

void printUsers() {
    int i;
    for (i = 0; i < kullaniciSayisi; i++) {
        printf("Kullanici adi: %s\n", users[i].name);
        printf("Hesap numarasi: %d\n", users[i].hesapNo);
        printf("Bakiye: %.2lf\n\n", users[i].bakiye);
    }
}

void paraYatirma() {
    int hesapNo;
    printf("Hesap numaranizi giriniz: ");
    scanf("%d", &hesapNo);

    int i, miktar;
    for (i = 0; i < kullaniciSayisi; i++) {
        if (users[i].hesapNo == hesapNo) {
            printf("Ne kadar para yatirmak istiyorsunuz?");
            scanf("%d", &miktar);
            users[i].bakiye += miktar;

            saveDataToFile();
            return;
        }
    }

    printf("Hesap numarasi bulunamadi.\n");
}

void paraCekme() {
    int hesapNo;
    printf("Hesap numaranizi giriniz: ");
    scanf("%d", &hesapNo);

    int i, miktar;
    for (i = 0; i < kullaniciSayisi; i++) {
        if (users[i].hesapNo == hesapNo) {
            printf("Ne kadar para cekmek istiyorsunuz?");
            scanf("%d", &miktar);
            if (users[i].bakiye >= miktar) {
                users[i].bakiye -= miktar;
                printf("Para cekildi.\n");

                saveDataToFile();
                return;
            } else {
                printf("Yetersiz bakiye.\n");
                return;
            }
        }
    }

    printf("Hesap numarasi bulunamadi.\n");
}

int main() {
    loadDataFromFile();

    int choice;

    while (1) {
        printf("1. Yeni hesap olustur\n");
        printf("2. Hesap guncelle\n");
        printf("3. Hesap sil\n");
        printf("4. Kullanicilari listele\n");
        printf("5. Para Yatirma\n");
        printf("6. Para Cekme\n");
        printf("7. Cikis\n");
        printf("Seciminizi yapin: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createUser();
                break;
            case 2:
                updateUser();
                break;
            case 3:
                deleteUser();
                break;
            case 4:
                printUsers();
                break;
            case 5:
                paraYatirma();
                break;
            case 6:
                paraCekme();
                break;
            case 7:
                saveDataToFile();
                exit(0);
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }
    }

    return 0;
}

