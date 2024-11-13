#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Deklarasi objek LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variabel untuk kontrol game
int pos = 0;
int y = 1;
const int buttonPin = 2;
const int buzzerPin = 4;
bool gameOver = false;
int score = 0; // Variabel untuk menyimpan angka skor

// Membuat karakter khusus
byte Tengkorak[8] = {
  B01110,
  B11111,
  B11111,
  B10101,
  B11111,
  B11111,
  B11011,
  B01110
};

byte Menara[8] = {
  B00000,
  B00100,
  B01110,
  B01110,
  B01110,
  B01110,
  B11111,
  B11011
};

void setup() {
  lcd.init();               // Inisialisasi LCD
  lcd.backlight();          // Menyalakan backlight LCD
  lcd.createChar(0, Tengkorak); // Membuat karakter "Tengkorak"
  lcd.createChar(1, Menara);  // Membuat karakter "Menara"
  
  pinMode(buttonPin, INPUT_PULLUP); // Mengatur tombol sebagai input dengan pull-up
  pinMode(buzzerPin, OUTPUT);      // Mengatur buzzer sebagai output
}

void loop() {
  if (gameOver) {
    return; // Menghentikan loop jika game over
  }

  // Bersihkan layar dan tampilkan Menara
  lcd.clear();
  for(int i = 0; i < 4; i++) {
    lcd.setCursor(3 + (i * 3), 1);
    lcd.write((byte)1);
  }

  // Cek apakah tombol ditekan untuk membuat Tengkorak melompat
  if (digitalRead(buttonPin) == LOW) {
    y = 0;  // Tengkorak melompat
    tone(buzzerPin, 2000); // Aktifkan buzzer dengan frekuensi 2000 Hz
  } else {
    y = 1;  // Tengkorak kembali ke bawah
    noTone(buzzerPin);     // Matikan suara buzzer
  }

  // Cek apakah Tengkorak menabrak Menara
  if (y == 1 && (pos == 3 || pos == 6 || pos == 9 || pos == 12)) {
    // Jika ki arjuno berada di posisi Menara, Game Over
    tone(buzzerPin, 500, 300); // Nada rendah untuk Game Over
    delay(300);
    tone(buzzerPin, 400, 300);
    delay(300);
    tone(buzzerPin, 300, 500);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Anda Gagal");
    lcd.setCursor(3, 1);
    lcd.print("   Score ");
    lcd.setCursor(12, 1); // Menampilkan skor di samping tulisan Game Over
    lcd.print(score);     // Tampilkan skor yang sudah dicapai
    gameOver = true; // Set game over flag
    score = 0; // Reset skor saat Game Over
    return;
  }

  // Tampilkan Tengkorak di posisi tertentu
  lcd.setCursor(pos, y);
  lcd.write((byte)0);

  // Gerakkan Tengkorak ke kanan
  pos++;
  if (pos > 15) {
    pos = 0;
    // Tengkorak mencapai ujung kanan, beri suara "point" dan tambahkan skor
    tone(buzzerPin, 2000, 100); // Nada tinggi untuk "point"
    delay(100);
    noTone(buzzerPin);
    score++; // Tambahkan skor
  }

  // Tampilkan angka skor di pojok kanan atas layar
  lcd.setCursor(14, 0);
  lcd.print(score);

  // Delay untuk mengontrol kecepatan animasi
  delay(225);
}