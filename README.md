# ${{\color{green}Hyla}}Sound$
<p align="center">
    <img src="resources/images/hylasound.png" width="200" height="200" />
</p>

Basic soundboard, you can add your audio files to create buttons in the soundboard and play them. I will later try to send the audio output through the mic so that people in voice chat can also hear your sounds. I am developping this as one of the surprises for my girlfriend for our first year anniversary. If you don't see how this is romantic, don't worry about it.

### Screenshots

![Application look on Linux](resources/images/github/hylasound_linux.png)
<p align="center"><em>Here is what the application looks like on Linux with Adwaita-Dark theme</em><p>

***

![Application look on Windows](resources/images/github/hylasound_windows.png)
<p align="center"><em>Here is what the application looks like on Windows with no Qt theme installed</em><p>

### Build
Linux with debugging and compile commands for Vim:
```bash
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug
make -C build -j$(nproc)
```
Linux using Ninja instead of Make:
```bash
cmake -S . -B build -G Ninja
ninja -C build
```
Windows:
```bash
cmake -B build
cmake --build build --parallel --config Release
# Not necessary, bundles Qt dependecies
cmake --install build --config Release --prefix "C:\absolute\path\dist"
```
MacOS:

I don't know :/ I don't have a Mac but should be similar.
