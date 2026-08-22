## Képernyőkép/Screenshots

<p align="center">
  <img src="https://github.com/gidano/LVGL-Radio/blob/main/Photos/LVGL-Radio.jpg" alt="480x320" width="480"><img src="https://github.com/gidano/LVGL-Radio/blob/main/Photos/LVGL-Radio_2.jpg" alt="480x320" width="480">
</p>

## LVGL Radio - ESP32-S3, ILI9488 / ST7796, XPT2046 / FT6X36, PCM5102A

- Külön FT6X36 touch profil.
- ILI9488 és ST7796 kijelzőprofil támogatás.
- LovyanGFX `Touch_FT5x06` meghajtó.
- I²C adatkapcsolat.
- SDA: GPIO8.
- SCL: GPIO9.
- INT: GPIO41.
- RESET: GPIO42.
- I²C-cím: `0x38`.
- I²C-órajel: 400 kHz.
- Érintési tartomány: 320 × 480.
- XPT2046 SPI-konfiguráció megtartva.
- `TS_MISO` és `TS_CS` csak XPT2046 módban.

Touch fájlok:

- `options.h`
- `options_touch_ft6x36.h`
- `options_touch_xpt2046.h`
- `src/display/DisplayDevice.h`
- `src/display/DisplayDevice.cpp`

## Kijelző színeinek invertálása

- Új kapcsoló a WebUI Háttér paneljén.
- Azonnali alkalmazás mentéskor.
- Tartós mentés a Preferences tárhelyre.
- Automatikus visszaállítás újraindításkor.
- Preferences-kulcs: `color_inv`.
- WebAPI-mező: `background.invertColors`.
- A WebUI változása miatt LittleFS-feltöltés szükséges.

Invertálási fájlok:

- `data/web/settings_hu.html`
- `src/web/RadioWebServer.cpp`
- `src/app/RadioController.h`
- `src/app/RadioController.cpp`
- `src/display/DisplayManager.h`
- `src/display/DisplayManager.cpp`

---

# LVGL Radio – ESP32-S3, ILI9488 / ST7796, XPT2046 / FT6X36, PCM5102A

Moduláris LVGL-alapú internet és helyi hálózati zenelejátszó az
`options.h` hardverkiosztásához.

## Támogatott kijelző- és érintésprofilok

- Alapértelmezett saját rádió: ILI9488 + XPT2046.
- Kapacitív ILI9488 tesztprofil: ILI9488 + FT6X36.
- ST7796 kijelzőprofil: ST7796 + XPT2046 vagy ST7796 + FT6X36.
- Az ST7796 build az `options.h` fájlban a `DISPLAY_PROFILE_ST7796` kapcsolóval
  választható.
- Az FT6X36 kapacitív érintésprofil az `options.h` fájlban a
  `TOUCH_PROFILE_FT6X36` kapcsolóval választható.

## Felépítés

- `src/app`: az alkalmazás vezérlése
- `src/audio`: audio-vezérlés és HTTP M3U lejátszás
- `lib/MaleksmAudioI2S`: a yoRadio-ból átvett, PSRAM-ra hangolt audio-motor
- `src/display`: kijelző, érintés, képernyők és a 480 pixeles VU
- `src/network`: Wi-Fi kezelés
- `src/stations`: myRadio-kompatibilis állomáslista
- `src/web`: webkiszolgáló és myRadio-kompatibilis API
- `data/web`: a böngészős kezelőfelület
- `data/logos`: az állomáslogók
- `data/cache`: az állomáslogók gyorsítótára
- `data/moon_phases`: a dátumvezérelt holdfázis PNG képek
- `data/fonts`: az LVGL bináris, ékezetes fontjai

## Könyvtárverziók

- Arduino-ESP32 3.3.7
- Maleksm/Wolle ESP32-audioI2S 3.4.6w (helyi projektkönyvtár)
- LVGL 9.3.0
- LovyanGFX 1.2.24

A PlatformIO az LVGL-t és a LovyanGFX-et a `platformio.ini` alapján
automatikusan kezeli. Az audio-könyvtár a projekt része, ezért nem cserélődik
le egy későbbi, eltérően viselkedő kiadásra.

## Aktuális kijelzőállapot

- Az állomáslogó panel LVGL szinten klippelt / lekerekített sarkokat használ.
  Ez csak a kirajzolást érinti, a logófájlokat, a `nologo.png` működését és
  az `.sr565` cache-kezelést nem módosítja.
- A holdfázis megjelenítés külön PNG ágon működik. A képek a
  `/moon_phases/moon_phase_0.png` ... `/moon_phases/moon_phase_7.png`
  útvonalakon vannak, 90 × 82 px méretben.
- A dátum szerinti képkiválasztás a szinódikus holdhónapot 8 középre igazított
  szeletre osztja, ezért a telihold kép csak a ciklus közepén jelenik meg, nem
  pusztán magas megvilágítottsági százaléknál.
- A holdkép pozíciója a spektrum látható jobb széle és az óra bal oldala
  közötti területhez van igazítva.
- A hold PNG alfa csatornája megmarad, a majdnem fekete szélek finoman
  áttetszővé válnak, hogy háttérképeken ne jelenjen meg fekete keret.
- Az időjárás szövegsor a hold beillesztése után 4 px-lel feljebb került.
- A VU / spektrum szegmensvonalai csak az oszlopokon belül látszanak, az
  oszlopok közötti hézagokat nem rajzolják át.
- A VU / spektrum teljes vászonfrissítést használ. Ez fontos, mert a részleges
  frissítés ezen a kijelzőn fekete sávot okozott a háttérképes megjelenítésnél.
- A vizualizáció módja webes beállításból is választható: spektrum,
  sztereó VU vagy üres alsó sáv. Ez nem érintőképernyős használatnál is
  elérhetővé teszi a váltást.
- Ugyanebben a webes panelben az érintéses fejléc- és logóváltások is
  állíthatók: LVGL Radio / IP, Wi-Fi ikon / szöveg, grafikus / szöveges
  hangerő, illetve logó / diagnosztika.
- A TFT SPI írási órajel jelenleg 40 MHz. Ez a tesztek alapján csökkentette a
  CPU1 terhelést, de kijelzőhibák esetén visszaállítható konzervatívabb értékre.
- A diagnosztikai nézetben a hangpuffer címkéje `BUFFER`, a többi angol
  mérőértékhez igazítva.

Fontos fejlesztési szabály: a működő állomáslogó-kezelést nem szabad
átalakítani más funkció kedvéért. A `nologo.png`, a webes PNG logó és az
`.sr565` cache útvonalai maradjanak stabilak; a holdfázis kép külön ágon él.

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

Fontos: a böngészős webfelület négy nyelven elkészült, de maga a rádió
kijelzőfelülete jelenleg nem teljesen többnyelvű. A rádió oldali szövegek,
névnapfájlok és kijelzőn megjelenő üzenetek többnyelvűsítése külön fejlesztési
feladat.

```powershell
$radioIp = "A_RADIO_IP_CIME"
curl.exe -F "path=/web/index_hu.html" -F "file=@data/web/index_hu.html" "http://$radioIp/upload"
curl.exe -F "path=/web/index_en.html" -F "file=@data/web/index_en.html" "http://$radioIp/upload"
curl.exe -F "path=/web/index_de.html" -F "file=@data/web/index_de.html" "http://$radioIp/upload"
curl.exe -F "path=/web/index_pl.html" -F "file=@data/web/index_pl.html" "http://$radioIp/upload"
```

## LittleFS File Manager Wi-Fi v0.6.0-kapcsolat

A firmware kompatibilis a
`WiFi_manager_v0.6.0` csomagban lévő Wi‑Fi Partition Managerrel.
A programban válaszd a **WiFi / IP** kapcsolatot, majd add meg a kijelzőn
látható rádió-IP-címet (később az LVGL Radio feliratot érintve hívható elő).
Portot vagy külön útvonalat nem kell megadni.

Ajánlott kiegészítő partíciófájlok Wi-Fi-s kezeléséhez:
[LittleFS-SPIFFS_File_Manager_WiFi_v0.6.0](https://github.com/gidano/myRadio-SPIFFS-Manager/tree/main/LittleFS-SPIFFS%20Partition%20Manager).

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

Ajánlott kiegészítő állomáslista Wi-Fi-s kezeléséhez:
[myRadio Stations Editor](https://github.com/gidano/myRadio-Stations-Editor).

A webfelület az eszköz IP-címén érhető el. Állomást választ, hangerőt és
fényerőt állít, listát szerkeszt, valamint külön lépteti az M3U zeneszámait.

PC-n lévő zenei mappák hálózati streameléséhez használható kiegészítő:
[myRadio Music Server](https://github.com/gidano/myRadio-Music-Server).

## Encoder kezelés

- Két encoderes bekötésnél az első encoder forgatása normál rádióképernyőn az
  előző / következő állomásra vált, a második encoder a hangerőt állítja.
- Egy encoderes bekötésnél, amikor az `ENC2_*` lábak nincsenek definiálva, az
  első encoder forgatása normál rádióképernyőn a hangerőt állítja.
- Az első encoder hosszú nyomása megnyitja a teljes képernyős
  állomásválasztót.
- Az első encoder rövid nyomása lejátszás / szünet kapcsolóként működik.
- A teljes képernyős állomásválasztóban az első encoder forgatása a listát
  görgeti, nem vált azonnal állomást.
- A kijelölt állomás a meglévő biztonsági késleltetéssel indul: ha a kijelölés
  3 másodpercig nem változik, a rádió átvált az adott adóra.
- A hosszú nyomás nem indítja el a rövid nyomáshoz tartozó lejátszás / szünet
  műveletet.

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

Az ILI9488 kapacitív és ST7796 kijelzők kezeléséban nyújtott segítségért köszönet illeti: ([<b>Simon Zsolt</b>](https://github.com/SimZs))

---
# English Summary

## LVGL Radio - ESP32-S3, ILI9488 / ST7796, XPT2046 / FT6X36, PCM5102A

This project is a modular LVGL-based internet radio and local network music
player for the hardware layout defined in `options.h`.

## Supported Display And Touch Profiles

- Default own-radio build: ILI9488 + XPT2046.
- Capacitive ILI9488 test profile: ILI9488 + FT6X36.
- ST7796 display profile: ST7796 + XPT2046 or ST7796 + FT6X36.
- The ST7796 build is selected in `options.h` with the
  `DISPLAY_PROFILE_ST7796` switch.
- The FT6X36 capacitive touch profile is selected in `options.h` with the
  `TOUCH_PROFILE_FT6X36` switch.

## Structure

- `src/app`: application control
- `src/audio`: audio control and HTTP M3U playback
- `lib/MaleksmAudioI2S`: yoRadio-derived audio engine tuned for PSRAM
- `src/display`: display, touch, screens, and 480-pixel VU visualization
- `src/network`: Wi-Fi handling
- `src/stations`: myRadio-compatible station list
- `src/web`: web server and myRadio-compatible API
- `data/web`: browser-based control interface
- `data/logos`: station logos
- `data/cache`: station logo cache
- `data/moon_phases`: date-driven moon phase PNG images
- `data/fonts`: binary LVGL fonts with accented characters

## Library Versions

- Arduino-ESP32 3.3.7
- Maleksm/Wolle ESP32-audioI2S 3.4.6w, included locally in the project
- LVGL 9.3.0
- LovyanGFX 1.2.24

PlatformIO manages LVGL and LovyanGFX through `platformio.ini`. The audio
library is part of the project, so it will not silently change to a later
release with different behavior.

## Current Display State

- The station logo panel uses LVGL-side corner clipping / rounding. This only
  affects rendering and does not modify logo files, `nologo.png`, or `.sr565`
  cache handling.
- Moon phase rendering uses its own PNG path. Files are stored as
  `/moon_phases/moon_phase_0.png` ... `/moon_phases/moon_phase_7.png`, with a
  current size of 90 × 82 px.
- Date-based image selection divides the synodic lunar month into 8 centered
  slices, so the full moon image appears around the middle of the cycle, not
  merely when illumination is high.
- The moon image is positioned between the visible right edge of the spectrum
  and the left edge of the clock.
- PNG alpha is preserved for the moon image, and nearly black edge pixels are
  faded so the black frame does not appear on background images.
- The weather text row was moved 4 px upward after adding the moon image.
- VU / spectrum segment separator lines are drawn only inside the columns, not
  across the gaps between bars.
- The VU / spectrum uses full canvas invalidation. This is intentional because
  partial invalidation caused black bands around the visualization when
  background images were used.
- The visualization mode can also be selected from the web settings: spectrum,
  stereo VU, or blank bottom band. This makes the setting available even
  without a touchscreen.
- The same web panel also exposes touch-only header and logo toggles: LVGL
  Radio / IP, Wi-Fi icon / text, graphical / textual volume, and logo /
  diagnostics.
- TFT SPI write speed is currently 40 MHz. Testing showed reduced CPU1 load,
  but it can be reverted if display artifacts appear.
- The diagnostics view uses `BUFFER` for the audio buffer label, matching the
  other English labels.

Development rule: do not rework the working station logo handling for other
features. The `nologo.png`, web PNG logo, and `.sr565` cache paths should stay
stable; the moon phase image lives on a separate display path.

## Build And Upload

```text
pio run
pio run --target upload
pio run --target uploadfs
```

`uploadfs` uses the project-specific fix kept in this repository, so it is
more stable on this board. It is mainly needed when the full local `data`
folder has to be uploaded to the radio's LittleFS partition.

The four main web UI language pages can also be refreshed separately without
rewriting the rest of LittleFS:

Important: the browser-based web UI is available in four languages, but the
radio display UI itself is not fully multilingual yet. Multilingual radio-side
labels, nameday files, and on-screen messages are a separate future task.

```powershell
$radioIp = "RADIO_IP_ADDRESS"
curl.exe -F "path=/web/index_hu.html" -F "file=@data/web/index_hu.html" "http://$radioIp/upload"
curl.exe -F "path=/web/index_en.html" -F "file=@data/web/index_en.html" "http://$radioIp/upload"
curl.exe -F "path=/web/index_de.html" -F "file=@data/web/index_de.html" "http://$radioIp/upload"
curl.exe -F "path=/web/index_pl.html" -F "file=@data/web/index_pl.html" "http://$radioIp/upload"
```

## LittleFS File Manager Over Wi-Fi

The firmware is compatible with the Wi-Fi Partition Manager from the
`WiFi_manager_v0.6.0` package. Select the **WiFi / IP** connection and enter
the radio IP address shown on the display (It can be accessed later by tapping the ‘LVGL Radio’ label). No custom port or path is required.

Recommended companion tool for managing partition files over Wi-Fi:
[LittleFS-SPIFFS_File_Manager_WiFi_v0.6.0](https://github.com/gidano/myRadio-SPIFFS-Manager/tree/main/LittleFS-SPIFFS%20Partition%20Manager).

Supported Wi-Fi file operations:

- list the complete LittleFS directory tree
- upload and download files
- create and delete folders
- delete files
- restart the radio

When the file manager connects, the radio enters a maintenance mode: playback
and LVGL refresh are stopped so active fonts and cache files can be replaced.
Use the Partition Manager **Restart** command when finished. The file manager
API is not password-protected on the local network, so use it only on a trusted
network.

## First Wi-Fi Setup

If `/wifi.txt` does not exist in LittleFS, the radio creates the
`LVGL-Radio-Setup` access point. Connect to it, open the IP address shown on
the display, then enter the Wi-Fi network name and password. The password is
not stored in the project data folder.

## Station List

The `/stations.txt` line format is:

```text
Station name<TAB>stream or M3U URL<TAB>logo file name
```

Example:

```text
PC/ZENE - KEVERT	http://192.168.31.101:8000/playlist_shuffle.m3u	music_server
```

The previous **myRadio Stations Editor** remains compatible:

- read list: `GET /api/stations`
- upload full list: multipart `POST /upload`
- target path: `/stations.txt`

Recommended companion tool for managing station lists over Wi-Fi:
[myRadio Stations Editor](https://github.com/gidano/myRadio-Stations-Editor).

The web UI is available at the device IP address. It can select stations,
adjust volume and brightness, edit the station list, and step through M3U
tracks.

Companion tool for streaming music folders from a PC on the local network:
[myRadio Music Server](https://github.com/gidano/myRadio-Music-Server).

## Encoder Controls

- With a two-encoder wiring, rotating the first encoder on the normal radio
  screen switches to the previous / next station, while the second encoder
  adjusts volume.
- With a one-encoder wiring, when the `ENC2_*` pins are not defined, rotating
  the first encoder on the normal radio screen adjusts volume.
- Long-pressing the first encoder opens the full-screen station selector.
- Short-pressing the first encoder toggles play / pause.
- While the station selector is open, rotating the first encoder scrolls the
  list instead of switching stations immediately.
- The selected station starts with the existing safety delay: if the selection
  does not change for 3 seconds, the radio switches to that station.
- A long press does not also trigger the short-press play / pause action.

## Settings And Time

The web UI settings panel can change and save the time zone immediately.
Budapest / Central Europe handles daylight saving time automatically. London,
Helsinki, UTC, and custom POSIX time zone values are also available. Saved
settings survive restart.

## M3U Network Music

The player accepts UTF-8 M3U files where absolute HTTP/HTTPS MP3 URLs follow
the `#EXTM3U` header. `#EXTINF` lines are optional. The displayed track title
is generated from the URL file and folder name. At the end of a track, the next
entry starts automatically.

## Fonts And Touch

The accented 20 px and 28 px LVGL fonts are loaded from LittleFS, with a
firmware fallback font available. Space (`U+0020`) is included in both fonts.

Touch calibration is stored in NVS and normally runs only once. To recalibrate,
hold the first encoder button (`GPIO5`) during power-on or reset.

We would like to thank ([<b>Simon Zsolt</b>](https://github.com/SimZs)) for their assistance with the ILI9488 capacitive and ST7796 displays!
