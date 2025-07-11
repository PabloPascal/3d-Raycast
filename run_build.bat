mkdir build
cd build 
cmake ..
cmake --build . --config Release
cd ..
copy external/SFML-2.6.1/bin/openal32.dll build/Release
copy external/SFML-2.6.1/bin/sfml-audio-2.dll build/Release
copy external/SFML-2.6.1/bin/sfml-audio-d-2.dll build/Release
copy external/SFML-2.6.1/bin/sfml-graphics-2.dll build/Release
copy external/SFML-2.6.1/bin/sfml-graphics-d-2.dll build/Release
copy external/SFML-2.6.1/bin/sfml-system-2.dll build/Release
copy external/SFML-2.6.1/bin/sfml-system-d-2.dll build/Release
copy external/SFML-2.6.1/bin/sfml-window-2.dll build/Release
copy external/SFML-2.6.1/bin/sfml-window-d-2.dll build/Release

 