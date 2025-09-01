#include <stdio.h>
#include <string.h>
#include <strings.h>
#define MAX_PELAJAR 100
#define PANJANG_NAMA 50

typedef struct {
  int id;
  char nama[PANJANG_NAMA];
  float nilai;
} Siswa;

void tambah_siswa(Siswa siswa[], int *hitung, int id, const char *nama,
                  float nilai) {
  if (*hitung >= MAX_PELAJAR) {
    fprintf(stderr, "error: max capacity pelajar sudah sampai\n");
    return;
  }

  siswa[*hitung].id = id;
  strncpy(siswa[*hitung].nama, nama, PANJANG_NAMA - 1);
  siswa[*hitung].nama[PANJANG_NAMA - 1] = '\0'; // null terminated
  siswa[*hitung].nilai = nilai;
  (*hitung)++;
  printf("siswa `%s` sudah ditambahkan\n", nama);
}

int cari_data_siswa(const Siswa siswa[], int hitung, int id) {
  for (int i = 0; i < hitung; i++) {
    if (siswa[i].id == id) {
      return i;
    }
  }
  return -1;
}

void tampilin_data_siswa(const Siswa siswa[], int hitung) {
  if (hitung == 0) {
    printf("tidak ada data siswa yang tersedia\n");
    return;
  }
  printf("data siswa tersedia:\n");
  for (int i = 0; i < hitung; i++) {
    printf("id: %d || nama: %s || nilai: %.2f\n", siswa[i].id, siswa[i].nama,
           siswa[i].nilai);
  }
}

float hitung_rata_nilai(const Siswa siswa[], int hitung) {
  if (hitung == 0) {
    return 0.0f;
  }
  float hasil = 0.0f;
  for (int i = 0; i < hitung; i++) {
    hasil += siswa[i].nilai;
  }

  return hasil / hitung;
}

int main() {
  // int array[5] = {10, 20, 30, 40, 50};
  // int angka[10];
  //
  // float nilai[5] = {0.0};
  // char name[30] = "arfy";
  // int *pointer = array;
  // pointer = &array[0];

  // printf("array: %p\n", (void *)array); // alamat awal dari si array
  // printf("&array: %p\n",
  //        (void *)&array); // integer reference dari si ukuran array size
  // printf("sizeof dari si array: %zu\n",
  //        sizeof(array)); // 20 byte, karena array 5 tipe integer 4 byte jadi
  //        5 x
  //                        // 4 = 20 byte
  // printf("sizeof dari pointer %zu\n",
  //        sizeof(pointer)); // Ukuran dari pointernya decay aja, jadi 8 byte

  Siswa siswa[MAX_PELAJAR];
  int jumlah_siswa = 0;
  tambah_siswa(siswa, &jumlah_siswa, 101, "yo", 70.2);
  tambah_siswa(siswa, &jumlah_siswa, 102, "ab", 80.52);
  tambah_siswa(siswa, &jumlah_siswa, 102, "ay", 90.22);

  // tampilin_data_siswa(siswa, jumlah_siswa);

  int index = cari_data_siswa(siswa, jumlah_siswa, 102);

  if (index != -1) {
    printf("data ditemukan \n");
    printf("data: %s (nilai: %.2f)\n", siswa[index].nama, siswa[index].nilai);
  } else {
    printf("Data tidak temukan \n");
  }

  float rata_rata = hitung_rata_nilai(siswa, jumlah_siswa);
  printf("rata-rata nilai adalah: %.2f\n", rata_rata);

  return 0;
}

// Static array cukup
// klo dinamis malloc + pointer
// Define dalam konstanta ukuran array, batas array penting menghindari buffer
// overflow struct untuk data yang kompleks
