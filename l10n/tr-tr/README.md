# Stumpless
**Yüksek performans ve zengin özellik seti için oluşturulmuş bir C günlükleme (logging) kütüphanesi.**

[![Linux Builds](https://github.com/goatshriek/stumpless/actions/workflows/linux.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/linux.yml)
[![Windows Builds](https://github.com/goatshriek/stumpless/actions/workflows/windows.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/windows.yml)

[English](../../README.md) | [Français](../fr-fr/README.md) | [한국어](../ko-kr/README.md) | [简体中文](../zh-cn/自述.md) | [Türkçe](../tr-tr/README.md)

[Ana Özellikler](#ana-ozellikler) |
[Kurulum](#hizli-kurulum) |
[Temel Kullanım](#temel-kullanim) |
[Katkıda Bulunma](#katkida-bulunma)

## Ana Özellikler
Stumpless, C dilinde günlüklemeyi (logging) hızlı ve kolay hale getiren birçok özelliğe sahiptir:
* Splunk, rsyslog, journald, Windows Olay Günlüğü (Event Log), sqlite3 ve daha fazlasına günlük gönderin!
* İhtiyaçlarınıza uygun yapılandırılmış (structured) ve yapılandırılmamış günlükleme.
* Linux, Windows, Mac, FreeBSD, DOS ve daha fazlasında derlenebilir!
* İş parçacığı güvenliği (thread safe).
* Çoklu dil desteği (Türkçe dahil! 🇹🇷).

### Nerelere günlük (log) gönderebilir?
Stumpless şunlara günlük yazabilir:
* Basit karakter arabellekleri (buffers)
* Dosyalar ve akışlar (streams)
* Unix soketleri
* Ağ sunucuları (IPv4 veya IPv6, TCP veya UDP)
* Sqlite3 veritabanları
* Windows Olay Günlüğü (Event Log)

## Hızlı Kurulum
Stumpless derlemek için sadece `cmake` ve GCC veya Visual Studio gibi bir derleyiciye ihtiyaç duyar.

```sh
# kaynak kodun en son sürümünü kopyalamak
git clone git@github.com:goatshriek/stumpless.git

# yeni bir build dizini oluşturmak
mkdir build
cd build

# yeni derlemeyi yapılandırmak
cmake ../stumpless

# stumpless'ı derlemek
cmake --build . --parallel 4