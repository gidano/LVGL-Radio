# LVGL Radio – funkcióösszefoglaló / functionality summary

Last updated / Utoljára frissítve: 2026-08-05

---

## Magyar

### Általános leírás

Az LVGL Radio egy ESP32-S3 alapú internetes rádió felület, amely LVGL kijelzőkezelést, LittleFS fájlrendszert, webes kezelőfelületet, állomáslogó-kezelést, időjárás-megjelenítést és valós idejű audió-vizualizációt használ.

### Fő funkciók

- internetes rádióállomások lejátszása
- station lista kezelése LittleFS-ben a `stations.txt` fájl alapján
- webes kezelőfelület állomás- és beállításkezeléshez
- állomáslogók megjelenítése
- diagnosztikai nézet CPU / RAM / PSRAM / hőmérséklet / puffer adatokkal
- időjárási adatok megjelenítése Open-Meteo alapokon
- dátum és névnap megjelenítése
- spektrum / VU audió-vizualizáció
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
- Diagnosztikai nézetben a logó helyén diagnosztikai panel jelenhet meg

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

### Webes kezelőfelület

#### Fő lehetőségek

- állomáslista kezelése
- állomások keresése és szerkesztése
- logókezelés
- beállítások oldal
- időjárás beállítása
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
- időjárás ikonok: `/weather_icons_48`
- webes állományok: `/web`

### Jelenlegi megjelenítési sajátosságok

- a rádiólogók és időjárás ikonok stabil megjelenítéséhez optimalizált formátum használható
- az időjárás ikonok jelenlegi, használt készlete 48×48-as megjelenítésre van optimalizálva
- az időjárás sor és az ikon a dátumsor alja és a VU teteje közti sávban helyezkedik el

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
- A kezelőfelület több pontján érintéses váltások működnek, ezért a képernyőelemek pozicionálása és az érintési zónák mérete kiemelten fontos.

### Ismert korlátok / planned features

#### Ismert korlátok

- A képernyőn elérhető hely korlátozza az időjárás ikon maximális méretét.
- Hosszú szövegek esetén egyes mezők csonkolással jelennek meg a scrollozás elkerülése érdekében.
- Az időjárás ikonokhoz és egyes vizuális elemekhez még lehetnek további finomhangolási lehetőségek.

#### Tervezett / lehetséges jövőbeli fejlesztések

- 4 nyelvű teljes felület
- bővebb webes settings oldal
- theme / színkezelés webes beállításból
- időjárási piktogram és időjárási sor további finomhangolása
- teljes képernyős állomásválasztó nézet
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
- Időjárás ikonok: `/weather_icons_48`
- Webes fájlok: `/web`

---

## English

### General description

LVGL Radio is an ESP32-S3 based internet radio interface using LVGL for display handling, LittleFS for storage, a web UI for management, station logo handling, weather display, and real-time audio visualization.

### Main features

- internet radio playback
- station list handling based on `stations.txt` in LittleFS
- web interface for station and settings management
- station logo display
- diagnostic view with CPU / RAM / PSRAM / temperature / buffer data
- weather information display based on Open-Meteo
- date and nameday display
- spectrum / VU audio visualization
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
- In diagnostic mode, the logo area can be replaced by a diagnostics panel

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
- weather icons: `/weather_icons_48`
- web assets: `/web`

### Current display-specific notes

- optimized formats can be used for stable rendering of station logos and weather icons
- the currently used weather icon set is optimized for 48×48 display usage
- the weather icon and weather text row are placed in the band between the bottom of the date row and the top of the VU area

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
- Because several screen areas use touch-based toggles, object placement and touch-zone sizing are important parts of the UI design.

### Known issues / planned features

#### Known issues

- Available screen space limits the maximum weather icon size.
- Some long text fields are truncated instead of scrolling, to avoid layout and performance issues.
- Weather icon and weather-row visuals can still be fine-tuned further.

#### Planned / possible future improvements

- full 4-language interface
- expanded web settings page
- theme / color handling from the web UI
- further fine-tuning of weather pictograms and weather row
- full-screen station selector view
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

#### Web control

- The radio provides a web UI accessible from a browser.
- The web UI can be used for:
  - station list management
  - search / editing
  - weather setup
  - time setup
  - file management

#### Files

- Stations: `stations.txt`
- Wi-Fi data: `wifi.txt`
- Logos: `/logos`
- Weather icons: `/weather_icons_48`
- Web assets: `/web`
