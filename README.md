# Textile Weaver

Weave different textile patterns into one Textile.

# Structure

+ **TexGenerator** is used to generate textile patterns.

+ **TexHelper** is used to weave a textile from multiple patterns.

# Examples:

A long exmaple
```batch
texgenerator --filename tex1.txt --interval 7 --origin 1 --size 32
texgenerator --filename tex1.txt --interval 7 --origin 9 --size 32
texgenerator --filename tex2.txt --interval 6 --origin 3 --size 32
texgenerator --filename tex2.txt --interval 6 --origin 16 --size 32
texgenerator --filename tex2.txt --interval 7 --origin 19 --size 32
texgenerator --filename tex3.txt --interval 9 --origin 20 --size 32
texgenerator --filename tex4.txt --interval 8 --origin 31 --size 32
texgenerator --filename tex5.txt --interval 1 --origin 12 --size 32
texgenerator --filename tex6.txt --interval 0 --origin 23 --size 32
texgenerator --filename tex7.txt --interval 22 --origin 13 --size 32
texgenerator --filename tex8.txt --interval 15 --origin 32 --size 32
texgenerator --filename tex9.txt --interval 6 --origin 8 --size 32
texgenerator --filename tex10.txt --interval 9 --origin 6 --size 32

texhelper --input-number 10 --size 32 tex1.txt tex2.txt tex3.txt tex4.txt tex5.txt tex6.txt tex7.txt tex8.txt tex9.txt tex10.txt --output-filename texWeaveSuccess.txt
``````
A small exmaple
```batch
texgenerator -f tex21.txt -i 5 -o 3 -s 16
texgenerator -f tex22.txt -i 6 -o 8 -s 16
texgenerator -f tex23.txt -i 9 -o 6 -s 16
texhelper -n 3 -s 16 tex21.txt tex22.txt tex23.txt -o texWeaveMini.txt
``````
