# <b><p align="center">Nästa »  Mini</p></b>

<p align="center">
  A little box that tells you when the next SL (Stockholm Local Transport) departure is leaving.<br>One glance on your way out the door and you'll know if you can stroll or if you need to sprint.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/board-Waveshare%20ESP32--S3--Matrix-4682B4?style=flat-square" />
  <img src="https://img.shields.io/badge/framework-ESP--IDF-E44D26?style=flat-square" />
  <img src="https://img.shields.io/badge/API-SL%20Transport-006AB3?style=flat-square" />
</p>

---

<p align="center">
  <img src="docs/images/product_shot_head_on.png" width="300" alt="Nästa Mini showing next departure" />
</p>

The <i>Nästa Mini</i> built around an ESP32-S3 with an 8×8 RGB LED matrix and a single push button on the back. Run through the setup portal once, and from then on it just sits there showing your next departure in a color that does the thinking for you.

| Color | Meaning |
|---|---|
| ![](https://img.shields.io/badge/-red-ff2200?style=flat-square) | means you're already too late.
| ![](https://img.shields.io/badge/-orange-ff8800?style=flat-square) | means hurry up.
| ![](https://img.shields.io/badge/-green-00cc44?style=flat-square) or ![](https://img.shields.io/badge/-white-ffffff?style=flat-square) |  means relax, take your time.

It only shows one direction at a time, but switching is easy: a short button press toggles between direction 1 and direction 2. Use one to glance at your own commute out, and the other to keep an eye on when someone else is due to arrive.

A long press drops you into setup mode.

## Setup

On first boot (or after a long button press), the device opens its own Wi-Fi access point called `nasta-mini-setup`. Connect to it and a captive portal should pop up on its own. If your phone or laptop is being stubborn about it, just open `http://setup.nasta-mini/` in a browser yourself. From there you can set:

- Your Wi-Fi credentials
- The SL site ID for your stop
- A transport mode filter (any, metro, train, bus, tram)
- Walk time in minutes (sets up when the color gradient is triggered)
- Brightness, startup direction, and display orientation

Don't know your stop's SL site ID off the top of your head? Nobody does. Look it up in Trafiklab's SL stop data tools and grab the numeric `site_id`.

## Display states

The matrix talks to you in color and the occasional symbol. Here's the full vocabulary:

| &nbsp; | State | Meaning |
|:---:|---|---|
| ![](https://placehold.co/14x14/dddddd/dddddd.png) | Boot animation | Starting up |
| ![](https://placehold.co/14x14/ff2200/ff2200.png)![](https://placehold.co/14x14/ff8800/ff8800.png)![](https://placehold.co/14x14/ffdd00/ffdd00.png)![](https://placehold.co/14x14/00cc44/00cc44.png)![](https://placehold.co/14x14/0066ff/0066ff.png)![](https://placehold.co/14x14/9900cc/9900cc.png) | Color wheel | Connecting to Wi-Fi |
| ![](https://placehold.co/14x14/33bb55/33bb55.png) | Green "OK" | Connected, waiting for first data |
| ![](https://placehold.co/14x14/888888/888888.png) | Pulsating white animation | Setup mode |
| ![](https://placehold.co/14x14/ff0000/ff0000.png)![](https://placehold.co/14x14/ff3300/ff3300.png)![](https://placehold.co/14x14/ff8800/ff8800.png)![](https://placehold.co/14x14/aacc00/aacc00.png)![](https://placehold.co/14x14/00cc44/00cc44.png)![](https://placehold.co/14x14/dddddd/dddddd.png) | Color ramp | Departure in N minutes. Color reflects urgency |
| ![](https://placehold.co/14x14/ffcc00/ffcc00.png) | Yellow `?` | No departures available |
| ![](https://placehold.co/14x14/ff2200/ff2200.png) | Red `?` | API error |
| ![](https://placehold.co/14x14/ff2200/ff2200.png) | Red `x` | Network error |

## Hardware

<img src="docs/images/product_shot_side.png" width="260" align="right" alt="Nästa Mini mounted on a wall" />

Built and tested on the [Waveshare ESP32-S3-Matrix](https://www.waveshare.com/esp32-s3-matrix.htm) development board, which already packages the ESP32-S3 and the 8×8 RGB LED matrix together. The only thing added on afterward is a push button on the back.

- **MCU**: ESP32-S3
- **Display**: 8×8 RGB LED matrix
- **Input**: one push button

The electronics lives inside a two-part 3D printed case. Print files are in [hardware/3d-print/](hardware/3d-print/):

- [`front_v.1.0.3mf`](hardware/3d-print/front_v.1.0.3mf)
- [`back_v.1.0.3mf`](hardware/3d-print/back_v.1.0.3mf)

## API

Departures come from the [SL Transport API](https://www.trafiklab.se/sv/api/our-apis/sl/transport/), polled every 10 seconds. Only departures with state `EXPECTED` make the cut.

This product is based on information retrieved from [Trafiklab.se](https://www.trafiklab.se/).

## Building

Tested with ESP-IDF `v5.5.3` for target `esp32s3`.

Open an ESP-IDF shell and build/flash like you would any other ESP-IDF project:

```sh
idf.py set-target esp32s3
idf.py build
idf.py -p <PORT> flash monitor
```

Thanks for reading, now go catch your ride!

## License
This repository is source-available, not open source. See [LICENSE](LICENSE) for the governing terms.

Third-party software notices live in [THIRD-PARTY-NOTICES.md](THIRD-PARTY-NOTICES.md).
