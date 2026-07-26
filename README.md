
> [!WARNING]
> This project is currently work-in-progress. (WIP)

<div align="center">
    <h2>
        <i>Solutions to Exercises of<br>The C Programming Language 2nd Edition by K&R</i>
    </h2>
    <p>
        <i>
            Solutions to all exercises from the book "The C Programming Language 2nd
            Edition by Brian W. Kernighan & Dennis M. Ritchie".
        </i>
    </p>
</div>

## Getting A Compiler
#### Windows
Windows users can choose MSVC C compiler or GCC through
MinGW(Minimal GNU for Windows). The latter is preferred and easier to install. One of the
ways to install MinGW is through [MSYS2↗](https://www.msys2.org/). Through it, you can
get very up-to-date version of GCC.<br /><br />

Install MSYS2 from the link provided and open it. It will open a terminal where you will
install MinGW with the following commands:

> [!NOTE]
> There are two commands, the $ must be excluded, it's present to indicate you must run
> the command in a command prompt/shell. Copy the 2 commands separately and paste them to
> your terminal and hit <ENTER>
```
$ pacman -Su
$ pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

After the installation of MinGW is done, you have to add the path:
`C:\msys64\ucrt64\bin` to your Environment Variables by,<br /><br />


Opening Search Bar > Typing "Environment Variables" and entering >
clicking "Environment Variables..." > Under "System Variables" clicking on "Path" and
pressing "Edit..." > Adding the path mentioned here to the list >
pressing OK to all the boxes.


#### Linux
Run the one of the commands depending on your version of linux:
```
# ARCH LINUX
sudo pacman -Sy base-devel

# DEBIAN LINUX
sudo apt update && sudo apt install build-essential

# VOID LINUX
sudo xbps-install -S base-devel

# ALPINE LINUX
doas apk add gcc
```

#### macOS
Please view other resources to install GCC on a Mac. The reason it's not included as it is
two descriptive and a video would greatly help.

## Project Structure
The project is structured very simply and starts at `src/`:
```
src
    chapter_i
        exercise_i-j.c
```

### Running an exercise
Before we can run an exercise, you must open or change directory of your terminal to the
root of the project. And compile & run the source of an exercise with the following
commands:
```
# Pseudo-command:
# $ gcc src/chapter_i/exercise_i-j.c

# Examples:
$ gcc src/chapter_1/exercises_1-12.c
$ gcc src/chapter_2/exercises_2-3.c
$ gcc src/chapter_3/exercises_3-5.c
$ gcc src/chapter_4/exercises_4-3.c

# And run with (on Mac or Linux)
$ ./a.out
# (or on Windows)
$ .\a.exe
```

## Contributing
Currently the project is under development and not all the solutions are solved.
Please, do not open a Pull Request solving any future problem that I have not solved.
<br /><br />

If you've found a mistake in my solutions, you are welcome to open a Issue or Pull
Request! I will be glad to review it.<br /><br />

Any help with documentation such as misspelling, unclear meaning etc. are also accepted.
<br /><br />

Thanks.
