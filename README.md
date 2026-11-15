# C++ Modern Toolkit

C++20 programs exploring modules, regular expressions, filesystem traversal, ranges and asynchronous execution, alongside an SFML sorting visualizer.

Author: Wiktor J. Dziendziel.

## Programs

| Directory | Behavior |
| --- | --- |
| `modules/` | Named modules and partitions: arithmetic, parity, powers, factorials, maximum, array sum, person/student models and animal sounds. |
| `regex/` | Checks a fixed email pattern, converts date-shaped text and counts mixed-case matches. |
| `filesystem/` | Prints path properties, counts file extensions recursively and totals sizes of `.tmp`/`.log` files. It does not delete them. |
| `ranges/` | Checks vector membership, prints squares of even numbers and processes response times after a `-1` marker. |
| `concurrency/` | Demonstrates `async`, futures, promises, threads and packaged tasks. |
| `sorting-visualizer/` | Animates bubble, selection, insertion and cocktail sorting, with step navigation and text history export. |

These are separate executables. Most program output and the visualizer interface are in Polish. The console programs use fixed examples rather than command-line arguments or interactive input.

## Build and run

Use a C++20 compiler and standard library. The module project retains Visual Studio toolset **v145**, Windows SDK **10.0**, and its original build options. The graphics program additionally requires **SFML 3** headers/libraries (Graphics, Window and System), inferred from the API used in its source. No library binaries or fonts are bundled.

### Console programs on Windows

In an x64 Native Tools command prompt for Visual Studio, from the repository root:

```bat
mkdir build
cl /nologo /std:c++20 /EHsc /utf-8 regex\main.cpp /Fo:build\regex.obj /Fe:build\regex.exe
cl /nologo /std:c++20 /EHsc /utf-8 filesystem\main.cpp /Fo:build\filesystem.obj /Fe:build\filesystem.exe
cl /nologo /std:c++20 /EHsc /utf-8 ranges\main.cpp /Fo:build\ranges.obj /Fe:build\ranges.exe
cl /nologo /std:c++20 /EHsc /utf-8 concurrency\main.cpp /Fo:build\concurrency.obj /Fe:build\concurrency.exe
build\regex.exe
cd filesystem
..\build\filesystem.exe
cd ..\ranges
..\build\ranges.exe
cd ..
build\concurrency.exe
```

Run filesystem and ranges from their respective directories because they use relative input paths. `filesystem/sample-data/` contains small synthetic files; replace them with your own files if needed. `ranges/dane.txt` is an independently created numeric example. Its output includes ten values from `1.701s` through `2.5s`; values before the marker and values at or below `1700.1` are omitted.

For modules, open `modules/Modules.vcxproj` in Visual Studio, or run:

```bat
msbuild modules\Modules.vcxproj /p:Configuration=Debug /p:Platform=x64
modules\x64\Debug\Modules.exe
```

Both versions of the module program were successfully built and run using direct MSVC commands. The MSBuild route encountered an environment access restriction; see limitations below.

### Console programs with a Unix-like toolchain

From each console program's directory, a direct build command is:

```sh
c++ -std=c++20 -O3 -pedantic-errors main.cpp -o main
./main
```

For concurrency, also pass `-pthread`. These commands require a compatible compiler/library and were not exercised on a Unix-like host. The ranges program relies on transitive declarations for `std::ranges::find`, which some toolchains may reject; this existing portability issue is unchanged.

### Sorting visualizer

The existing runtime expects the macOS font `/System/Library/Fonts/Menlo.ttc`. Use a machine where that system font is available. Font discovery and failure behavior have not been changed for other operating systems.

From `sorting-visualizer/`, with SFML 3 available to `pkg-config`:

```sh
mkdir -p build
c++ -std=c++20 -O3 -pedantic-errors $(pkg-config --cflags sfml-graphics sfml-window sfml-system) src/*.cpp -o build/sorting-visualizer $(pkg-config --libs sfml-graphics sfml-window sfml-system)
./build/sorting-visualizer
```

This direct command is provided from the source dependencies; the full graphics build was not verified in the preparation environment.

Use the algorithm arrows to switch sorting methods. `Nastepny`/`Poprzedni` navigate steps, `Auto-Sort` starts playback, `Stop` pauses, and the slider changes speed. `Reset` generates ten new values in the range 1–50. `Historia` displays recorded operations; `Zapisz` writes a text file into `historia/` relative to the current directory. Escape closes the window.

The algorithms record array states and operation descriptions; rendering and UI read those states. History export uses an asynchronous operation. The displayed complexity information is descriptive text and is not a benchmark.

## Validation and limitations

There was no existing automated test suite. During release preparation, the original and staged console sources were built with MSVC, and outputs were compared using the same synthetic inputs. Filesystem missing-directory exits (1), ranges missing-file exits (0), regex cases, and the sorting core were checked. All four sorting algorithms produced identical operation histories and navigation states for empty, singleton, sorted, reversed and duplicate/negative-value arrays. Generator empty/fixed-value and negative-count behavior was also compared.

The console comparison accounts for neutral section headings, the input-directory rename, and the intentional switch of the email domain to `example.org`. The regex retains its original unescaped dot, so it is a demonstration pattern, not a general or strict email validator. Date replacement does not validate calendar dates.

Both concurrency executables printed totals of 13 and packaged-call results of 5 and 15, then exited with Windows status `0xC0000409` in the preparation environment. The cause was not established; successful termination is not claimed. Output can interleave between threads.

Both MSBuild attempts were blocked by a FileTracker access-denied error. A direct MSVC build (header units, partition interfaces, primary interfaces, then main and linking) succeeded for both versions; output matched after section-title normalization. The two arithmetic modules retain their duplicate `add` definitions; other compilers may handle them differently.

The full graphics build and interactive behavior were not tested because SFML was unavailable. The original font-loading behavior and UI quirks remain. Source for the visualizer is unchanged. No claim of full cross-platform compatibility is made.

No license grant is included in this snapshot. External compiler/runtime, SFML and system-font components remain separately supplied dependencies.
