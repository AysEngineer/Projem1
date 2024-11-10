# Projem1
## About my first project on GitHub. Work experience notes.
(OvcontSoftware)
Bu proje, bir ovcont için yazılmış bir mikrodenetleyici yazılımıdır. Yazılım, fırın sıcaklık kontrolü, dijital ekran yönetimi, buton taraması ve senkronizasyon gibi fonksiyonları içerir. Bu yazılım, BS86D20CA mikroişlemcisi ve özelleştirilmiş donanım platformu için geliştirilmiştir.

Proje Özeti
Bu yazılım, bir fırın kartının temel işlevlerini kontrol etmek için gereken algoritmaları içerir. Fırının çalışma sıklığı, dijital ekranın yönetimi, buton girişi taraması ve zamanlayıcı işlevselliği gibi fonksiyonları sağlar. Yazılım, yüksek hassasiyetli zamanlayıcılar ve kesme (interrupt) mekanizmaları kullanarak yüksek performans gereksinimlerini karşılamaktadır.

Özellikler
Zamanlayıcı Yönetimi: 125 mikro saniye aralıklarında çalışan bir zamanlayıcı ile yüksek hassasiyetli zaman kontrolü sağlanır.
Senkronizasyon Okuma: Senkronizasyon pininden gelen sinyalleri okuyarak fırın işleminin senkronizasyonunu sağlar.
Dijital Ekran Kontrolü: 4 haneli bir dijital ekranın kontrolünü yapar. Ekranda doğru veriyi görüntülemek için sırasıyla her bir basamağı tarar.
Buton Taraması: Butonların durumu periyodik olarak taranır ve kullanıcının girdiği komutlar işlenir.
Global Kesme (Interrupt) Yönetimi: Mikrodenetleyicinin kesme (interrupt) mekanizmalarını kullanarak sistemin belirli zaman aralıklarında (örneğin her 125 mikro saniyede bir) kesme hizmeti verir.
Kullanılan Teknolojiler
Mikrodenetleyici: BS86D20CA (16-bit mikrodenetleyici)
C Programlama Dili: Yazılım, C dilinde geliştirilmiştir ve mikrodenetleyiciyle uyumlu özel kütüphaneler kullanmaktadır.
Zamanlayıcılar: Sistem, yüksek doğruluklu zamanlayıcılarla donatılmıştır.
Kesme (Interrupt) Servis Rutini: Mikrodenetleyiciye ait kesme yönetimiyle zamanlayıcı ve buton taraması gerçekleştirilir.
Projeye Genel Bakış
Ana Fonksiyonlar
USER_PROGRAM_INITIAL: Donanım ayarları ve başlatma fonksiyonları burada yapılır. Mikrodenetleyici pinleri, zamanlayıcılar ve kesme servisleri konfigüre edilir.
ScanDisplay: 4 haneli dijital ekranın taranması ve her bir basamağın sırasıyla açılması sağlanır.
SyncRead: Fırının senkronizasyon sinyalleri okunur ve sistemin senkronize olma durumu kontrol edilir.
PTM Kesmesi: 125 mikro saniye aralıklarla tetiklenen kesme, zamanlayıcı ve ekran güncelleme işlemlerini yapar.
USER_PROGRAM: Ana döngüde fırın kontrolü, buton taraması ve ekran güncelleme işlemleri gerçekleştirilir.
Kullanıcı Arayüzü ve Girdi Kontrolleri
Proje, kullanıcıyla etkileşimde bulunmak için bir dizi buton ve dijital ekran kullanır. Bu yazılımda butonlar taranarak, kullanıcının isteklerine göre fırın kontrolü sağlanır.

Kurulum
Bu yazılımın çalışabilmesi için aşağıdaki adımlar gereklidir:

Gerekli Donanım:

BS86D20CA veya uyumlu bir mikrodenetleyici platformu.
4 haneli dijital ekran (LED veya 7-segment ekran).
Butonlar ve gerekli giriş/çıkış pinleri.
Yazılımın Derlenmesi:

C dilinde yazılmış olan bu yazılım, uygun bir mikrodenetleyici derleyicisi ile derlenmelidir. (HT-IDE)
Derleme için gerekli kütüphaneler ve başlık dosyaları (USER_PROGRAM.INC, BS86D20CA.h, defines.h, stdint.h) projeye dahil edilmelidir.
Yazılımın Yüklenmesi:

Derlenen yazılım, mikrodenetleyiciye yüklenmelidir. Yazılım, mikrodenetleyiciye uygun bir programlayıcıyla (örneğin,e-link_HOltek veya ISP) yüklenebilir.

