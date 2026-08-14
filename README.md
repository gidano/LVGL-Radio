# LVGL Radio – ESP32-S3, ILI9488, XPT2046, PCM5102A

Moduláris LVGL-alapú internet és helyi hálózati zenelejátszó az
`options.h` hardverkiosztásához.

## Felépítés

- `src/app`: az alkalmazás vezérlése
- `src/audio`: audio-vezérlés és HTTP M3U lejátszás
- `lib/MaleksmAudioI2S`: a yoRadio maleksm-mod-ból átvett, PSRAM-ra hangolt audio-motor
- `src/display`: kijelző, érintés, képernyők és a 480 pixeles VU
- `src/network`: Wi-Fi kezelés
- `src/stations`: myRadio-kompatibilis állomáslista
- `src/web`: webkiszolgáló és myRadio-kompatibilis API
- `data/web`: a böngészős kezelőfelület
- `data/logos`: az állomáslogók
- `data/fonts`: az LVGL bináris, ékezetes fontjai
- `data/backgrounds`: a használt képernyő-háttérképek mappája
- `data/presets`: a kedvencek képernyő mentett állomásait tartalmazza

## Könyvtárverziók

- Arduino-ESP32 3.3.7
- Wolle/Maleksm ESP32-audioI2S 3.4.6w (helyi projektkönyvtár)
- LVGL 9.3.0
- LovyanGFX 1.2.24

A PlatformIO az LVGL-t és a LovyanGFX-et a `platformio.ini` alapján
automatikusan kezeli. Az audio-könyvtár a projekt része, ezért nem cserélődik
le egy későbbi, eltérően viselkedő kiadásra.

## Hardverkiosztás

| Funkció | GPIO |
|---|---:|
| TFT/érintő SPI SCK | 12 |
| TFT/érintő SPI MOSI | 11 |
| XPT2046 MISO | 13 |
| TFT CS | 18 |
| TFT DC | 10 |
| TFT RESET | nincs (`-1`) |
| XPT2046 CS | 42 |
| Háttérvilágítás | 14 |
| PCM5102A BCLK | 21 |
| PCM5102A LRC | 47 |
| PCM5102A DATA | 38 |

Fontos: a GPIO13 fizikailag be van kötve az XPT2046 miatt, de az ILI9488
panel olvasása tiltott. Az `options.h` fájlban a `TFT_MISO` ezért marad
kikommentezve; csak a `TS_MISO` aktív.

## Fordítás és feltöltés

```text
pio run
pio run --target upload
pio run --target uploadfs
```

Az `uploadfs` ennél a lapnál a projektben hagyott külön javítással fut,
így stabilabban használható. Erre főleg akkor lehet szükség, ha a teljes
helyi `data` mappát akarod egyben feltenni a rádió LittleFS partíciójára.

A kezelőfelület négy nyelvi főoldala külön, a többi LittleFS-adat
érintése nélkül is frissíthető. A firmware feltöltése után PowerShellben:

```powershell
$radioIp = "A_RADIO_IP_CIME"
curl.exe -F "path=/web/index_hu.html" -F "file=@data/web/index_hu.html" "http://$radioIp/upload"
curl.exe -F "path=/web/index_en.html" -F "file=@data/web/index_en.html" "http://$radioIp/upload"
curl.exe -F "path=/web/index_de.html" -F "file=@data/web/index_de.html" "http://$radioIp/upload"
curl.exe -F "path=/web/index_pl.html" -F "file=@data/web/index_pl.html" "http://$radioIp/upload"
```

## LittleFS Partition Manager Wi-Fi-kapcsolat

A firmware kompatibilis a
`WiFi_manager_v0.6.0` csomagban lévő Wi‑Fi Partition Managerrel.
A programban válaszd a **WiFi / IP** kapcsolatot, majd add meg a kijelzőn
látható rádió-IP-címet. Portot vagy külön útvonalat nem kell megadni.

Wi‑Fi-n elérhető műveletek:

- teljes LittleFS könyvtárfa listázása;
- fájlok feltöltése és letöltése;
- könyvtárak létrehozása és törlése;
- fájlok törlése;
- a rádió újraindítása.

Ezzel az egyes fájlok módosításához nincs szükség külön soros
`uploadfs` feltöltésre.
Ha viszont a teljes helyi `data` mappát szeretnéd egyszerre újraírni,
az `uploadfs` továbbra is használható.
A Wi‑Fi fájlkezelő csatlakozásakor a rádió biztonsági karbantartási módba
lép: leáll a lejátszás és az LVGL-frissítés, így a használatban lévő
fontok és cache-fájlok is cserélhetők. A munka végén használd a Partition
Manager **Újraindítás** parancsát a normál rádiómód visszaállításához.
A fájlkezelő API a helyi hálózaton nincs jelszóval védve, ezért csak
megbízható hálózaton használd.

## Első Wi-Fi beállítás

Ha a LittleFS-en még nincs `/wifi.txt`, a rádió létrehozza a
`LVGL-Radio-Setup` hozzáférési pontot. Csatlakozás után nyisd meg a kijelzőn
látható IP-címet (alapértelmezésben `192.168.4.1`), majd add meg a hálózat
nevét és jelszavát. A jelszó nem része a projekt adatkönyvtárának.

## Állomáslista

A `/stations.txt` sorformátuma:

```text
Állomás neve<TAB>stream vagy M3U URL<TAB>logófájl neve
```

Példa:

```text
PC/ZENE - KEVERT	http://192.168.31.101:8000/playlist_shuffle.m3u	music_server
```

A korábbi **myRadio Stations Editor** változtatás nélkül használható:

- lista olvasása: `GET /api/stations`
- teljes lista feltöltése: multipart `POST /upload`
- célútvonal: `/stations.txt`

A webfelület az eszköz IP-címén érhető el. Állomást választ, hangerőt és
fényerőt állít, listát szerkeszt, valamint külön lépteti az M3U zeneszámait.

## Beállítások és pontos idő

A webfelület **Beállítások** paneljén az időzóna azonnal módosítható és
elmenthető. A Budapest / Közép-Európa beállítás a téli és nyári
időszámítást automatikusan kezeli. London, Helsinki, UTC és egyéni POSIX
időzónaérték is választható. A mentett érték újraindítás után is megmarad.

## M3U hálózati zene

A lejátszó elfogadja az olyan UTF-8 M3U fájlokat is, amelyekben a
`#EXTM3U` fejléc után csak abszolút HTTP/HTTPS MP3-címek vannak. Az
`#EXTINF` sor nem kötelező. A megjelenített számcím a százalékosan kódolt
URL fájl- és mappanevéből készül. A szám végén a következő elem automatikusan
elindul.

## Fontok és érintés

Az ékezetes 20 és 28 pixeles LVGL-fontok a LittleFS-ről töltődnek be; a
firmware tartalékfontot is tartalmaz. A szóköz (`U+0020`) része mindkét
fontnak.

Az érintő kalibrációja NVS-be kerül, ezért csak egyszer fut le. Új
kalibráláshoz bekapcsolás vagy reset közben tartsd nyomva az első encoder
gombját (`GPIO5`).
