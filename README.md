passgen is a password generator, not a password manager. its for solely **generating** passwords
.
***Installation:***

**step 1: cloning the repo**

its simple, run this:
```
git clone https://github.com/cheezitlin/passgen.git
```
**step 2: compiling**

if you havent already, install gcc:

arch/arch like OSes:
```
sudo pacman -S gcc
```

ubuntu/any OS that uses apt:

```

sudo apt install gcc
```

fedora:

```
sudo dnf install gcc
```

*next,*

run this in the directory passgen was cloned in:
```
gcc passgen.c -o passgen
```

this will compile passgen.c as passgen.

*then,*

run this:

```
sudo cp passgen /usr/bin/passgen
```
this will make you able to run passgen by simply typing its name in the command line.

***how to use:***

**password generation:**

to generate a password, you can just run passgen with no flags, but to specify a certain length (e.g. 24), add the flag ```-l <length>```.
*for example:*
```passgen -l 24``` gave me ```���U���Ts7�,XKX�{'C7�j�n```. but this is a mess of symbols, sure, this can be secure, like taking longer then the life of the universe to guess secure, but this wont be accepted in most websites.

**character(set) exclusion:**

you can use the flag ```-e:``` to exclude the inputted sets if the syntax is proper,
the current flags for -e are:

```u``` -- exclude unicode.

```l``` -- exclude letters.

```n``` -- exclude numbers.

```s``` -- exclude spaces.

*for example:*
```passgen -l 24 -e:us``` would exclude unicode characters, and spaces. the output i got was ```r8by5YHBjtEcN2wBSmEnz5C3```.
