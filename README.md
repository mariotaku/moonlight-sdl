# Moonlight TV

Moonlight TV is a GUI front end for [Moonlight GameStream Client](https://moonlight-stream.org/). With some components from [moonlight-embedded](https://github.com/irtimmer/moonlight-embedded).
It was originally designed for LG webOS TVs, but may support running on more devices in the future.

## Features

* Supports up to 4 controllers
* Utilizes system hardware decoder to get best performance (webOS 2/3/4/5)
* Easy to port to other OSes (Now runs on macOS, Linux, Raspberry Pi)

## Screenshots

![Launcher](https://user-images.githubusercontent.com/830358/106390397-9c162380-642b-11eb-948f-529e7f0d5e5e.png)

![Settings](https://user-images.githubusercontent.com/830358/106390394-9a4c6000-642b-11eb-8870-3c8c6e4a5c78.png)

![In-game Overlay](https://user-images.githubusercontent.com/830358/106390396-9b7d8d00-642b-11eb-8f34-58ae4f037f2e.png)

## Download

### For webOS

[Easy installation with dev-manager-desktop](https://github.com/webosbrew/dev-manager-desktop) (recommended)

Or download IPK from [Latest release](https://github.com/mariotaku/moonlight-tv/releases/latest)

## [Installation Guide](https://github.com/mariotaku/moonlight-tv/wiki/Installation-Guide)

## [Compatibility Status](https://github.com/mariotaku/moonlight-tv/wiki/Compatibility-Status)

## [Gamepad Setup](https://github.com/mariotaku/moonlight-tv/wiki/Gamepad-Setup)

## (For developers) Building for webOS

 - Follow instructions [here](https://github.com/webosbrew/meta-lg-webos-ndk) to setup NDK
 - Create a directory e.g. `build` in project root directory, and `cd` into it.
 - run `cmake .. -DTARGET_WEBOS=ON`
 - run `make webos-package-moonlight` to get IPK package in `build` directory