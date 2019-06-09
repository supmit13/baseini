basic ini file parser

How to create a statically linkable (.a) file with liteini:
-----------------------------------------------------------

Creating static library for liteini.c:
Following directions from: https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index

# gcc -c liteini.c  -o static/liteini.o

# ar rcs static/libliteini.a static/liteini.o 

# chown -R supriyo:root .

# cp liteini.h <location of your application>  (Getting the file to the location where your application (its executable) will be able to find it.)

# mv static/libliteini.a /usr/local/lib/libliteini.a
