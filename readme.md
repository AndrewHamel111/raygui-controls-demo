# raygui Interactive Controls Demo

This is the source from my raygui Controls Demo. It should *not* be considered a quality reference for using raygui or creating dynamic layouts. It is also does not contain an exemplary or even necessary use of Preprocessor Macros, however I simply could not resist the dark magicks.

For convenience a build.bat is included, though if you follow the instructions in my [Raylib with Notepad++ video](https://youtu.be/gj6OXFWYKTA) or simply if you are familiar with gcc it is trivial to build. This command assumes raylib is installed at `C:/raylib/raylib`, gcc is accessible from PATH and that the target is Windows:

>gcc -o flag_demo.exe *.c C:\raylib\raylib\src\raylib.rc.data -s -static -Os -std=c99 -Wall -IC:\raylib\raylib\src -Iexternal -DPLATFORM_DESKTOP -lraylib -lopengl32 -lgdi32 -lwinmm

## Dependencies

[raysan5/raylib](https://github.com/raysan5/raylib)

[raysan5/raygui](https://github.com/raysan5/raygui)