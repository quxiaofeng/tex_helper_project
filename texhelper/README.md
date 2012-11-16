# 功能

将多个纹样编织到一起。

# Options

+ -n NUMBER   --input-number NUMBER      :default 4
+ -o FILENAME --output-filename FILENAME :default out.txt
+ -s NUMBER   --size NUMBER              :default 16

Examples:
```batch
texhelper -s 16 -n 4 tex1.txt tex2.txt tex3.txt tex4.txt -o out.txt
texhelper --size 16 --input-number 4 tex1.txt tex2.txt tex3.txt tex4.txt --output-filename out.txt
``````
