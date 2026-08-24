# LVGL Radio – funkcióösszefoglaló / functionality summary

Last updated / Utoljára frissítve: 2026-08-24

---

## Magyar

### Általános leírás

Az LVGL Radio egy ESP32-S3 alapú internetes rádió felület, amely LVGL kijelzőkezelést, LittleFS fájlrendszert, webes kezelőfelületet, állomáslogó-kezelést, időjárás-megjelenítést és valós idejű audió-vizualizációt használ. A kijelzőoldal ILI9488 és ST7796 profilokat is támogat.

### Támogatott kijelző- és érintésprofilok

- alapértelmezett saját rádió: ILI9488 + XPT2046
- kapacitív ILI9488 tesztprofil: ILI9488 + FT6X36
- ST7796 kijelzőprofil: ST7796 + XPT2046 vagy ST7796 + FT6X36
- az ST7796 build az `options.h` fájlban a `DISPLAY_PROFILE_ST7796` kapcsolóval választható
- az FT6X36 kapacitív érintésprofil az `options.h` fájlban a `TOUCH_PROFILE_FT6X36` kapcsolóval választható

### Fő funkciók

- internetes rádióállomások lejátszása
- station lista kezelése LittleFS-ben a `stations.txt` fájl alapján
- webes kezelőfelület állomás- és beállításkezeléshez
- állomáslogók megjelenítése
- album-/lemezborító keresése Last.fm, MusicBrainz / Cover Art Archive,
  iTunes és Deezer forrásokból
- diagnosztikai nézet CPU / RAM / PSRAM / hőmérséklet / puffer adatokkal
- időjárási adatok megjelenítése Open-Meteo alapokon (nincs szükség egyéni API-kulcsra!)
- dátum és névnap megjelenítése
- dátumvezérelt holdfázis PNG megjelenítés
- spektrum / VU audió-vizualizáció
- webes spektrum / VU / üres vizualizációs módválasztás, valamint a fejléc /
  logó érintéses váltásainak webes állítása
- 4 nyelvű webes kezelőfelület
- teljes képernyős állomásválasztó encoderes görgetéssel
- hangerőkezelés fejlécből és felugró panelből
- IP-cím megjelenítés az óra helyén

### Képernyőelemek és érintéses működés

#### 1. Teljes képernyő

- Rövid érintés: lejátszás / szünet váltás
- Megjegyzés: az egyes dedikált érintési területek ezt felülírhatják

#### 2. Bal felső Wi-Fi terület

- Grafikus Wi-Fi jelszint vagy szöveges RSSI nézet
- Érintésre vált a két megjelenítési mód között:
  - grafikus jelerősség
  - szöveges érték dBm-ben

#### 3. Jobb felső hangerő terület

- Grafikus hangerő nézet vagy szöveges hangerőérték
- Érintésre vált a két megjelenítési mód között
- A hangerő értéke például `9/21` formában jelenhet meg
- A hangerőpanel ugyanerről a területről is előhívható

#### 4. Hangerő felugró panel

- Vízszintes hangerőállításra jelenik meg
- Tartalma:
  - hangszóró ikon
  - csúszka
  - aktuális hangerőérték
- A csúszka húzásával közvetlen hangerőállítás lehetséges

#### 5. Óra / IP terület jobb alsó sarokban

- Induláskor először az IP-cím jelenik meg
- Kb. 10 másodperc után automatikusan órára vált
- Érintésre váltás lehetséges:
  - óra
  - IP-cím

#### 6. Állomáslogó / bal oldali logópanel

- Az aktuális állomás logóját mutatja
- A logópanel sarkai LVGL oldalon vannak finoman lekerekítve / klippelve, így a szögletes külső logóképek sarkai nem rajzolódnak ki.
- A logóképek, a `nologo.png` és az `.sr565` cache működő kezelése nincs átalakítva.
- A logó az alapállapot: album-borító csak sikeres letöltés és thumbnail-készítés után váltja le.
- Ha a borítókeresés sikertelen, kevés a puffer vagy kevés a belső RAM, a rádió az állomáslogót tartja meg.
- Diagnosztikai nézetben a logó helyén diagnosztikai panel jelenhet meg

#### 6/a. Album-borító keresés

- A borítókeresés akkor indul, ha a stream címe `Előadó - Cím` formában értelmezhető.
- Keresési sorrend:
  - Last.fm közvetlen képek és albumadatok
  - Last.fm MBID alapján MusicBrainz / Cover Art Archive release
  - MusicBrainz release-group / Cover Art Archive jelöltek
  - iTunes Search
  - Deezer Search
- A Last.fm használatához `LASTFM_API_KEY` kell az `options.h` fájlban.
- MusicBrainz, Cover Art Archive, iTunes és Deezer ehhez a kereséshez nem igényel külön API-kulcsot.
- A találat 128×128-as `.sr565` thumbnailként kerül cache-be.
- Dalváltáskor a korábbi albumhoz tartozó cache célzottan törölhető, az állomáslogó-cache megtartása mellett.
- A lejátszás folyamatosságának fenntartása elsőbbséget élvez: alacsony hangpuffer-állás mellett a borítólekérés szándékosan várakozik, vagy nem indul el az aktuális dalra.
- HTTPS stream vagy kevés belső heap esetén a keresés szintén várhat vagy kihagyhatja az aktuális dal borítóját, hogy a hang maradjon elsőbbségben.

#### 7. Állomásnév terület

- Érintésre a preset / állomásválasztó logika hívható meg
- A későbbi teljes képernyős állomáslista alapja lehet

#### 8. Időjárás ikon

- Az aktuális időjárási / előrejelzési piktogram jelenik meg
- Érintésre vált az előrejelzési módok között:
  - aktuális időjárás
  - mai előrejelzés
  - holnapi előrejelzés

#### 9. Dátum + névnap sor

- Középre rendezett megjelenítés
- A névnap rész hossza dinamikusan alkalmazkodik a rendelkezésre álló helyhez

#### 10. Időjárás szöveges sor

- Középre igazított sor
- A jelenlegi kijelzőelrendezésben 4 px-lel feljebb került, hogy a holdfázis-kép alatt/fölött tisztább legyen a tér.
- Megjeleníthet például:
  - hőmérséklet
  - légnyomás
  - páratartalom
  - szélsebesség
  - szélirány
- Előrejelzés módtól függően napi minimum / maximum és csapadék esély is látható

#### 11. Alsó audió-vizualizáció (VU / spektrum)

- Több megjelenítési módot támogat:
  - spektrum
  - sztereó VU
  - kikapcsolt állapot
- Érintésre a vizualizáció módjai között lehet váltani
- Bal oldalon L / R csatornajelölések láthatók
- A szegmensek közötti vízszintes elválasztók csak az oszlopokon belül rajzolódnak, az oszlopok közti hézagokban nem.
- A VU / spektrum teljes vászonfrissítést használ, mert ez őrzi meg stabilan a háttérképek áttetsző hatását. Korábbi részleges frissítés fekete sávot okozott a vizualizáció körül, ezért nem használható alapként.
- A vizualizáció módja a webes beállításokból is választható: spektrum, sztereó VU vagy üres alsó sáv. Ez a nem érintőképernyős használatot is támogatja.
- A webes beállításokból a fejléc és logó érintéssel váltott nézetei is állíthatók: LVGL Radio / IP, Wi-Fi ikon / szöveg, grafikus / szöveges hangerő és logó / diagnosztika.

#### 12. Holdfázis-kép

- A holdfázis külön PNG megjelenítési ágon működik, nem az állomáslogó-cache közösítésével.
- A képek helye: `/moon_phases/moon_phase_0.png` ... `/moon_phases/moon_phase_7.png`.
- A használt képméret: 90×82 px.
- A dátum szerinti választás a szinódikus holdhónapot 8 középre igazított szeletre osztja, így a növő / telő / fogyó állapotok sorrendje nem pusztán megvilágítottsági százalék alapján dől el.
- A kép a spektrum látható jobb széle és az óra bal oldala közötti területhez igazított pozícióban jelenik meg.
- A PNG alfa csatornája megmarad; a majdnem fekete szélek külön finomított áttetszőséget kapnak, hogy háttérképeken ne látszódjon fekete keret.

#### 13. Encoderes állomásválasztó

- Két encoderes bekötésnél az első encoder forgatása normál nézetben az előző / következő állomásra vált, a második encoder a hangerőt állítja.
- Egy encoderes bekötésnél, amikor az `ENC2_*` lábak nincsenek definiálva, az első encoder forgatása normál nézetben a hangerőt állítja.
- Az első encoder rövid nyomása lejátszás / szünet kapcsolóként működik.
- Az első encoder hosszú nyomása megnyitja a teljes képernyős állomásválasztót.
- Nyitott állomásválasztóban az első encoder forgatása a listát görgeti.
- A kijelölt állomás 3 másodperc változatlan kijelölés után indul el.
- Hosszú nyomáskor nem fut le mellette a rövid nyomásos lejátszás / szünet művelet.

### Webes kezelőfelület

#### Fő lehetőségek

- állomáslista kezelése
- állomások keresése és szerkesztése
- logókezelés
- beállítások oldal
- időjárás beállítása
- spektrum / VU / üres alsó kijelzősáv beállítása
- LVGL Radio / IP, Wi-Fi, hangerő és logó / diagnosztika nézet állítása
- időzóna / időbeállítás
- fájlkezelés LittleFS-en

#### Időjárás beállításai

- be / ki kapcsolás
- földrajzi szélesség / hosszúság
- frissítési időköz
- megjelenítési mód

### Fájlrendszer / LittleFS

- állomáslista: `stations.txt`
- Wi-Fi adatok: `wifi.txt`
- logók: `/logos`
- logó és album-borító cache: `/cache`
- holdfázis képek: `/moon_phases`
- időjárás ikonok: `/weather_icons_48`
- webes állományok: `/web`

### Kapcsolódó kiegészítő eszközök

- Partíció fájlok kezeléséhez Wi-Fi kapcsolaton: [LittleFS-SPIFFS_File_Manager_WiFi_v0.6.0](https://github.com/gidano/myRadio-SPIFFS-Manager/tree/main/LittleFS-SPIFFS%20Partition%20Manager)
- Állomáslista kezeléséhez Wi-Fi kapcsolaton: [myRadio Stations Editor](https://github.com/gidano/myRadio-Stations-Editor)
- PC-n lévő zenei mappák hálózati streameléséhez: [myRadio Music Server](https://github.com/gidano/myRadio-Music-Server)

### Jelenlegi megjelenítési sajátosságok

- a rádiólogók és időjárás ikonok stabil megjelenítéséhez optimalizált formátum használható
- az állomáslogó panel 12 px körüli sarokklippelést használ; ez csak a kirajzolást érinti, a logófájlokat és cache-t nem módosítja
- album-borító csak kész, érvényes cache-kép esetén jelenik meg; sikertelen keresésnél az állomáslogó marad
- a holdfázis-kép PNG-ként töltődik be a LittleFS-ről, külön kezelési ágon
- az időjárás ikonok jelenlegi, használt készlete 48×48-as megjelenítésre van optimalizálva
- az időjárás sor és az ikon a dátumsor alja és a VU teteje közti sávban helyezkedik el
- a kijelző SPI írási órajele jelenleg 40 MHz; teszt alapján ez csökkentette a CPU1 terhelést, de kijelzőhibák esetén visszaállítható konzervatívabb értékre

### Fejlesztői megjegyzések

- A projekt moduláris felépítésű, külön kezelve többek között:
  - audió logikát
  - kijelzőkezelést
  - webes felületet
  - időjárás kezelést
  - artwork / logókezelést
- A rendszer LittleFS-t használ tartalmak, logók, webes fájlok és segédállományok tárolására.
- Az állomáslogók és időjárás ikonok megjelenítésénél a stabil kirajzolás fontos szempont volt.
- Az időjárás ikonok jelenleg a kijelzőn bevált, stabil megjelenítési útvonalat használják.
- A működő állomáslogó-kezelést, beleértve a `nologo.png` és `.sr565` útvonalakat, más funkció kedvéért nem szabad átalakítani. A holdfázis megjelenítés külön PNG ágban marad.
- A v0.2 borítókeresés az állomáslogó-kezelés fölött, de attól elkülönítve működik: nem vehet el alapképet, csak sikeres találat után cserélhet.
- A nagy kép- és dekóderpufferek PSRAM-ba kerülnek, az LVGL tartalék rajzpuffer pedig nem foglal állandó belső RAM-ot. Ez kb. 10 kB belső RAM nyereséget adott a teszten.
- A VU / spektrum-nál teljes vászonfrissítés a stabil állapot.
- A vizualizáció módja Preferences-ben tárolódik (`vu_mode`), és webes settingsből is állítható.
- A nem érintős használatot segítő kijelzőállapotok Preferences-ben tárolódnak: `ui_ip`, `ui_wifi`, `ui_vol`, `ui_diag`.
- A webfelület 4 nyelven elkészült, de a rádió kijelzőfelülete jelenleg nem teljesen többnyelvű; a kijelzőn megjelenő szövegek, üzenetek és névnapfájlok többnyelvűsítése külön fejlesztési feladat.
- A kezelőfelület több pontján érintéses váltások működnek, ezért a képernyőelemek pozicionálása és az érintési zónák mérete kiemelten fontos.

### Ismert korlátok / planned features

#### Ismert korlátok

- A képernyőn elérhető hely korlátozza az időjárás ikon maximális méretét.
- Hosszú szövegek esetén egyes mezők csonkolással jelennek meg a scrollozás elkerülése érdekében.
- Az időjárás ikonokhoz és egyes vizuális elemekhez még lehetnek további finomhangolási lehetőségek.
- A CPU1 terhelés továbbra is figyelendő hosszabb 128 kbit/s MP3 lejátszás közben. A legutóbbi stabil irány a gyorsabb TFT írás volt, nem a vizualizáció látható működésének megváltoztatása.

#### Tervezett / lehetséges jövőbeli fejlesztések

- rádió oldali, webből váltható többnyelvű kijelzőfelület
- bővebb webes settings oldal
- theme / színkezelés webes beállításból
- időjárási piktogram és időjárási sor további finomhangolása
- további kényelmi elemek a webes és kijelzős kezeléshez

### Rövid felhasználói kézikönyv

#### Indítás

- A rádió indulás után betölti a mentett Wi-Fi kapcsolatot.
- Ha hálózati kapcsolat létrejön, megjelenik az aktuális állomás felülete.
- Az IP-cím induláskor rövid ideig látható, utána automatikusan órára vált.

#### Alap használat

- Koppintás a képernyőn: lejátszás / szünet
- Koppintás a Wi-Fi területen: grafikus / szöveges Wi-Fi nézet váltás
- Koppintás a hangerő területen: grafikus / szöveges hangerő nézet váltás
- Koppintás az óra területen: óra / IP-cím váltás
- Koppintás az időjárás ikonon: időjárás / mai / holnapi előrejelzés váltás
- Koppintás a VU / spektrum területen: vizualizációs mód váltás
- Két encoderrel első encoder forgatása: előző / következő állomás
- Egy encoderrel első encoder forgatása: hangerő állítása
- Első encoder hosszú nyomása: teljes képernyős állomásválasztó megnyitása
- Első encoder rövid nyomása: lejátszás / szünet
- Állomásválasztóban az első encoder forgatása: lista görgetése

#### Webes kezelés

- Böngészőből elérhető a rádió webes kezelőfelülete.
- A webes felületen kezelhető:
  - állomáslista
  - keresés / szerkesztés
  - időjárás beállítás
  - idő beállítás
  - fájlkezelés

#### Fájlok

- Állomások: `stations.txt`
- Wi-Fi adatok: `wifi.txt`
- Logók: `/logos`
- Logó cache: `/cache`
- Holdfázis képek: `/moon_phases`
- Időjárás ikonok: `/weather_icons_48`
- Webes fájlok: `/web`

---

## English

### General description

LVGL Radio is an ESP32-S3 based internet radio interface using LVGL for display handling, LittleFS for storage, a web UI for management, station logo handling, weather display, and real-time audio visualization. The display layer supports both ILI9488 and ST7796 profiles.

### Supported display and touch profiles

- default own-radio build: ILI9488 + XPT2046
- capacitive ILI9488 test profile: ILI9488 + FT6X36
- ST7796 display profile: ST7796 + XPT2046 or ST7796 + FT6X36
- the ST7796 build is selected in `options.h` with the `DISPLAY_PROFILE_ST7796` switch
- the FT6X36 capacitive touch profile is selected in `options.h` with the `TOUCH_PROFILE_FT6X36` switch

### Main features

- internet radio playback
- station list handling based on `stations.txt` in LittleFS
- web interface for station and settings management
- station logo display
- album artwork lookup from Last.fm, MusicBrainz / Cover Art Archive, iTunes,
  and Deezer
- diagnostic view with CPU / RAM / PSRAM / temperature / buffer data
- weather information display based on Open-Meteo (No individual API key is required!)
- date and nameday display
- date-driven moon phase PNG display
- spectrum / VU audio visualization
- web-selectable spectrum / VU / blank visualization mode, plus web control
  for header / logo views that are normally changed by touch
- 4-language browser-based web interface
- full-screen station selector with encoder scrolling
- volume control from the header and popup panel
- IP address display in the clock area

### Screen elements and touch behavior

#### 1. Full screen

- Short tap: play / pause toggle
- Note: dedicated touch zones can override this behavior

#### 2. Top-left Wi-Fi area

- Can show either graphical Wi-Fi strength or text RSSI view
- Tap toggles between:
  - graphical signal strength
  - text RSSI value in dBm

#### 3. Top-right volume area

- Can show either graphical volume or text volume value
- Tap toggles between the two display modes
- Volume can appear in a format such as `9/21`
- The same area can also trigger the volume popup

#### 4. Volume popup panel

- Appears during horizontal volume adjustment
- Contains:
  - speaker icon
  - slider
  - current volume value
- Direct volume adjustment is possible by dragging the slider

#### 5. Clock / IP area in the bottom-right corner

- On startup, the IP address is shown first
- After about 10 seconds, it automatically switches to the clock
- Tap can switch between:
  - clock
  - IP address

#### 6. Station logo / left logo panel

- Shows the current station logo
- The logo panel corners are softly rounded / clipped by LVGL, so square external logo corners are hidden.
- Existing handling for logo files, `nologo.png`, and the `.sr565` cache is not reworked.
- The station logo is the baseline image: album artwork replaces it only after a successful download and thumbnail conversion.
- If artwork lookup fails, the audio buffer is too low, or internal RAM is too low, the station logo stays visible.
- In diagnostic mode, the logo area can be replaced by a diagnostics panel

#### 6/a. Album artwork lookup

- Artwork lookup starts when stream metadata can be parsed as `Artist - Title`.
- Lookup order:
  - Last.fm direct images and album data
  - MusicBrainz / Cover Art Archive release through a Last.fm MBID
  - MusicBrainz release-group / Cover Art Archive candidates
  - iTunes Search
  - Deezer Search
- Last.fm requires `LASTFM_API_KEY` in `options.h`.
- MusicBrainz, Cover Art Archive, iTunes, and Deezer do not require a separate API key for this lookup.
- Successful artwork is cached as a 128×128 `.sr565` thumbnail.
- On track changes, the previous album cache can be removed without touching station-logo cache entries.
- Continuous playback has priority: when the audio buffer is low, artwork fetching intentionally waits or does not start for the current track.
- On HTTPS streams or low internal heap, lookup can also wait or skip the current track artwork so audio playback remains the priority.

#### 7. Station name area

- Tap can invoke preset / station selection logic
- This can later serve as the basis for a full-screen station list

#### 8. Weather icon

- Shows the current weather / forecast pictogram
- Tap cycles between forecast modes:
  - current weather
  - today forecast
  - tomorrow forecast

#### 9. Date + nameday row

- Center-aligned display
- Nameday length adapts dynamically to the available horizontal space

#### 10. Weather text row

- Center-aligned row
- In the current layout it is moved 4 px upward to keep cleaner spacing around the moon phase image.
- Can display for example:
  - temperature
  - pressure
  - humidity
  - wind speed
  - wind direction
- Depending on forecast mode, daily min / max and precipitation chance can also appear

#### 11. Bottom audio visualization (VU / spectrum)

- Supports multiple display modes:
  - spectrum
  - stereo VU
  - off
- Tap cycles through visualization modes
- L / R channel markers are shown on the left side
- Horizontal segment separators are drawn only inside the bars, not across the gaps between columns.
- The VU / spectrum uses full canvas invalidation because this reliably preserves the transparent background-image look. Earlier partial invalidation produced a black band around the visualization and is not a good baseline.
- The visualization mode can also be selected from web settings: spectrum, stereo VU, or blank bottom band. This supports builds without a touchscreen.
- Header and logo views normally toggled by touch can also be changed from web settings: LVGL Radio / IP, Wi-Fi icon / text, graphical / textual volume, and logo / diagnostics.

#### 12. Moon phase image

- Moon phase rendering uses a separate PNG path and is not merged into the station logo cache flow.
- Files are stored as `/moon_phases/moon_phase_0.png` ... `/moon_phases/moon_phase_7.png`.
- Current image size: 90×82 px.
- Date-based selection divides the synodic lunar month into 8 centered slices, so waxing / full / waning states are not chosen from illumination percentage alone.
- The image is positioned within the area between the visible right edge of the spectrum and the left edge of the clock.
- PNG alpha is preserved; nearly black border pixels receive a tuned fade so the black frame does not show on background images.

#### 13. Encoder Station Selector

- With two encoders, rotating the first encoder in normal view switches to the previous / next station, while the second encoder adjusts volume.
- With one encoder, when the `ENC2_*` pins are not defined, rotating the first encoder in normal view adjusts volume.
- Short-pressing the first encoder toggles play / pause.
- Long-pressing the first encoder opens the full-screen station selector.
- While the selector is open, rotating the first encoder scrolls the station list.
- The selected station starts after the selection remains unchanged for 3 seconds.
- A long press does not also trigger the short-press play / pause action.

### Web interface

#### Main capabilities

- station list management
- station search and editing
- logo handling
- settings page
- weather setup
- time zone / time setup
- file management on LittleFS

#### Weather settings

- enable / disable
- latitude / longitude
- refresh interval
- display mode

### File system / LittleFS

- station list: `stations.txt`
- Wi-Fi data: `wifi.txt`
- logos: `/logos`
- logo and album artwork cache: `/cache`
- moon phase images: `/moon_phases`
- weather icons: `/weather_icons_48`
- web assets: `/web`

### Related companion tools

- Managing partition files over Wi-Fi: [LittleFS-SPIFFS_File_Manager_WiFi_v0.6.0](https://github.com/gidano/myRadio-SPIFFS-Manager/tree/main/LittleFS-SPIFFS%20Partition%20Manager)
- Managing station lists over Wi-Fi: [myRadio Stations Editor](https://github.com/gidano/myRadio-Stations-Editor)
- Streaming music folders from a PC on the local network: [myRadio Music Server](https://github.com/gidano/myRadio-Music-Server)

### Current display-specific notes

- optimized formats can be used for stable rendering of station logos and weather icons
- the station logo panel uses about 12 px corner clipping; this affects rendering only and does not alter logo files or cache files
- album artwork is shown only after a valid cached image exists; failed lookup keeps the station logo visible
- the moon phase image is loaded from LittleFS as PNG through a separate display path
- the currently used weather icon set is optimized for 48×48 display usage
- the weather icon and weather text row are placed in the band between the bottom of the date row and the top of the VU area
- TFT SPI write speed is currently 40 MHz; testing showed lower CPU1 usage, but it can be reverted if display artifacts appear

### Developer notes

- The project follows a modular structure, separating for example:
  - audio logic
  - display handling
  - web UI
  - weather handling
  - artwork / logo handling
- The system uses LittleFS to store content, logos, web files, and support assets.
- Stable rendering has been an important goal for station logos and weather icons.
- Weather icons currently use the display path that proved stable on this hardware.
- The working station logo handling, including `nologo.png` and `.sr565` paths, should not be reworked for other features. Moon phase rendering stays on its own PNG path.
- The v0.2 artwork lookup works above the station-logo flow but remains separate from it: it cannot remove the baseline image, only replace it after a successful result.
- Large image and decoder buffers are steered to PSRAM, and the LVGL fallback draw buffer no longer permanently consumes internal RAM. Testing showed about 10 kB more internal RAM.
- Partial invalidation of the VU / spectrum broke background transparency on this display, so full canvas invalidation is the stable state.
- The diagnostics view uses `BUFFER` for the audio buffer label, matching the other English labels.
- The web UI is available in 4 languages, but the radio display UI itself is not fully multilingual yet; radio-side labels, messages, and nameday files are a separate development task.
- Because several screen areas use touch-based toggles, object placement and touch-zone sizing are important parts of the UI design.

### Known issues / planned features

#### Known issues

- Available screen space limits the maximum weather icon size.
- Some long text fields are truncated instead of scrolling, to avoid layout and performance issues.
- Weather icon and weather-row visuals can still be fine-tuned further.
- CPU1 load should still be observed during longer 128 kbit/s MP3 playback. The last stable optimization direction was faster TFT writes, not changing the visible behavior of the visualization.

#### Planned / possible future improvements

- web-selectable multilingual radio display UI
- expanded web settings page
- theme / color handling from the web UI
- further fine-tuning of weather pictograms and weather row
- more comfort features for both display and web control

### Short user manual

#### Startup

- On boot, the radio loads the saved Wi-Fi connection.
- Once network access is available, the current station screen is shown.
- The IP address is shown briefly at startup, then it automatically switches to the clock.

#### Basic usage

- Tap the screen: play / pause
- Tap the Wi-Fi area: switch graphical / textual Wi-Fi view
- Tap the volume area: switch graphical / textual volume view
- Tap the clock area: switch clock / IP address
- Tap the weather icon: switch current / today / tomorrow weather mode
- Tap the VU / spectrum area: switch visualization mode
- With two encoders, rotate the first encoder: previous / next station
- With one encoder, rotate the first encoder: adjust volume
- Long-press the first encoder: open the full-screen station selector
- Short-press the first encoder: play / pause
- Rotate the first encoder in the station selector: scroll the list

#### Web control

- The radio provides a web UI accessible from a browser.
- The web UI can be used for:
  - station list management
  - search / editing
  - weather setup
  - spectrum / VU / blank bottom-band setup
  - LVGL Radio / IP, Wi-Fi, volume, and logo / diagnostics view setup
  - time setup
  - file management

#### Files

- Stations: `stations.txt`
- Wi-Fi data: `wifi.txt`
- Logos: `/logos`
- Logo and album artwork cache: `/cache`
- Moon phase images: `/moon_phases`
- Weather icons: `/weather_icons_48`
- Web assets: `/web`
