<h1>Sistem Monitoring dan Kontrol Daya Listrik</h1>
<p>Sistem monitoring dan kontrol daya listrik berbasis IoT menggunakan microcontroller ESP32 dan module PZEM-004T<p>

## Development
### Visual Studio Code
#### Prerequisites
1. Wokwi for VS Code Extension: IoT and Embedded System Simulator
2. PlatformIO IDE for VS Code Extension: tool for embedded software development
3. Git: version control system (opsional)
#### Deskripsi
- Folder `src` berisi file `main.cpp` yang berisi kode program utama microcontroller
- File `diagram.json` berisi komponen yang digunakan untuk simulasi serta koneksi (wiring) antar komponen menggunakan Wokwi
- File `wokwi.toml` berisi konfigurasi untuk menjalankan simulasi menggunakan Wokwi for VS Code
- Untuk penjelasan lebih lanjut mengenai Wokwi for VS Code bisa lihat pada https://docs.wokwi.com/vscode/getting-started 
#### How To Run:
- Pastikan sudah menginstall ekstensi Wokwi dan PlatformIO IDE pada VS Code
- Lakukan `build` pada project dengan menekan `f1` > cari `PlatformIO: Build` > tekan enter untuk memulai proses build
- Buka file `diagram.json` lalu klik tombol hijau di pojok kiri atas untuk menjalankan simulasi. Jika diminta untuk memasukkan lisensi kunjungi https://wokwi.com/license
### Troubleshoot
#### Lisensi Wokwi for VS Code
Kunjungi https://wokwi.com/license untuk mendapatkan lisensi Wokwi. Login menggunakan akun email (bisa pakai gmail). Jika sudah login, tekan tombol `Get License Key`. Selanjutnya copy lisensi. Buka VS Code dan tekan `f1` untuk memunculkan Command Pallete. Kemudian pada kolom pencarian ketik `Wokwi: Manually Enter License Key` lalu paste lisensi yang sudah di copy.
#### Simulasi tidak terupdate meskipun isi `main.cpp` (kode program) diubah
Jika ketika kode program pada file `main.cpp` atau file lain yang digunakan untuk menjalankan program diubah, lalu simulasi dijalankan dan tidak menunjukkan perubahan. Maka, lakukan `build` ulang (_rebuild_) pada project menggunakan platformIO. Untuk informasi lebih lanjut lihat https://community.platformio.org/t/vsc-pio-why-it-does-not-update-upon-code-change-before-build/10210/7 

## Contributors 
- Muhammad Asral - [@asral168](https://github.com/asral168)
- Hadi Setiawan - [@Hdi28](https://github.com/Hdi28)
- Salman Amario Simpati - [@salmanamariosimpati](https://github.com/salmanamariosimpati)
- Ahmad Amin Badani - [@AminBadani](https://github.com/AminBadani)
