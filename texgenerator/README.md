# Fuction

This command is used to generate a tex pattern file.
The black spot is located in each line with same interval between lines.
And it can be written with different config again and again to make more black spots.

Currently the black spot is defined as "X", and and the white spot is defined as "blank".

# Options

+ -f FILENAME --filename FILENAME     :default tex.txt
+ -i NUMBER   --interval NUMBER       :default 1
+ -o NUMBER   --origin NUMBER         :default 1
+ -s NUMBER   --size NUMBER           :default 16
+ -r NUMBER   --row-number NUMBER     :default 16
+ -c NUMBER   --column-number NUMBER  :default 16
+ -x          --exchange-fb           :Exchange foreground and background
+ -a          --autogen               :Auto generate a batch of textiles

Examples:

```batch
texgenerator -f tex1.txt -i 3 -o 1 -s 16 -c 32 -r 64
texgenerator --filename tex2.txt --interval 6 --origin 3 --size 16 --column-number 32 --row-number 64
``````
