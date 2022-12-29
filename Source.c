#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define Double_Mantis_Boyutu 52
#define Double_Us_boyutu 11
#define Double_icin_EklenenSayi 1023
#define Float_Mantis_Boyutu 23
#define Float_Us_boyutu 8
#define Float_icin_EklenenSayi 127

void TamKisim_Binary_Cevir(char* tamkisim_dizi, int tam_kisim)
{
	int i = -1;

	while (tamkisim_dizi[++i] != '\0');
	i -= 1;

	while(i>=0 && tam_kisim!=0)
	{
		tamkisim_dizi[i--] = (tam_kisim % 2 == 0) ? '0' : '1';
		tam_kisim = tam_kisim / 2;
	}
}

int OndakliKisim_Rakam_SayisiBul(int* OndakliKisim, int* faktor)
{
	int RakamSayisi=1;

	*faktor = 1;

	while (*OndakliKisim>=10* *faktor)
	{ 
		RakamSayisi++;
		*faktor *= 10;
	}

	return RakamSayisi;
}
void OndakliKisim_Binary_Cevir(char* OndakliKisimBinaryDizi, int OndakliKisim, int mantis_boyut)
{
	int faktor, OndakliKisimAsilRakamSayisi, OndakliKisimRakamSayisi;

	OndakliKisimAsilRakamSayisi = OndakliKisim_Rakam_SayisiBul(&OndakliKisim, &faktor);

	int i = 0;

	while (i < mantis_boyut * 2 && OndakliKisim != 0)
	{
		OndakliKisim = OndakliKisim * 2;

		OndakliKisimRakamSayisi = OndakliKisim_Rakam_SayisiBul(&OndakliKisim, &faktor);

		if (OndakliKisimAsilRakamSayisi < OndakliKisimRakamSayisi)
		{
			OndakliKisimBinaryDizi[i++] = '1';
			OndakliKisim -= faktor;
		}
		else
		{
			OndakliKisimBinaryDizi[i++] = '0';
		}
	}
}


void Dizi_Sifir_ile_Doldur(char* dizi, int boyut)
{
	for (int i = 0; i < boyut; i++)
	{
		dizi[i] = '0';
	}
	dizi[boyut] = '\0';
}

int main()
{
	int Tamkisim, OndakliKisim, Mantis_Boyutu, Us_Boyutu;

	char TamkisimBinary[Double_Mantis_Boyutu + 1], OndakliKisimBinary[Double_Mantis_Boyutu * 2 + 1], Mantissa[Double_Mantis_Boyutu + 1], UsKisimBinary[Double_Us_boyutu + 1],
		secenek, isaretBiti;

	int UsSayi = 0, EklenenSayi;

	printf("Float icin 'f' ve Double icin 'd' Giriniz : ");
	scanf("%c", &secenek);

	printf("Tam kisim giriniz :");
	scanf("%d", &Tamkisim);

	printf("Ondakli Kisim Giriniz :");
	scanf("%d", &OndakliKisim);

	if (secenek == 'f')
	{
		Mantis_Boyutu = Float_Mantis_Boyutu;
		Us_Boyutu = Float_Us_boyutu;
		EklenenSayi = Float_icin_EklenenSayi;
	}
	else
	{
		Mantis_Boyutu = Double_Mantis_Boyutu;
		Us_Boyutu = Double_Us_boyutu;
		EklenenSayi = Double_icin_EklenenSayi;
	}

	Dizi_Sifir_ile_Doldur(TamkisimBinary,Mantis_Boyutu);
	Dizi_Sifir_ile_Doldur(OndakliKisimBinary, Mantis_Boyutu * 2);

	Dizi_Sifir_ile_Doldur(Mantissa, Mantis_Boyutu);
	Dizi_Sifir_ile_Doldur(UsKisimBinary, Us_Boyutu);

	isaretBiti = Tamkisim < 0 ? '1' : '0';

	TamKisim_Binary_Cevir(TamkisimBinary, Tamkisim);
	OndakliKisim_Binary_Cevir(OndakliKisimBinary, OndakliKisim, Mantis_Boyutu);

	int k = 0 ,i=0;
    
	if (Tamkisim == 0)
	{
		for (i = 0; i < Mantis_Boyutu; i++)
		{
			Mantissa[i] = '0';
		}
		UsSayi = -EklenenSayi;
	}
	else if (Tamkisim != 0)
	{
		while(TamkisimBinary[k++]=='0')
		{
			UsSayi = (Mantis_Boyutu - k);
		}

		for (i = 0; k < Mantis_Boyutu; k++, i++)
		{
			Mantissa[i] = TamkisimBinary[k];
		}

		for (k = 0; i < Mantis_Boyutu; k++, i++)
		{
			Mantissa[i] = OndakliKisimBinary[k];
		}
	}
	else
	{
		while (OndakliKisimBinary[k++] == '0');
		UsSayi = -k;

		for (i = 0; i < Mantis_Boyutu;k++, i++)
		{
			Mantissa[i] = OndakliKisimBinary[k];
		}
	}

	UsSayi += EklenenSayi;

	TamKisim_Binary_Cevir(UsKisimBinary,UsSayi);

	printf("Sonuc : %c\t%s\t%s", isaretBiti, UsKisimBinary, Mantissa);




	

}