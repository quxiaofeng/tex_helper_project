# 功能

这个命令用来生成纹样文件。

前景字符会根据指定起点(origin)，按照指定间隔(interval)分布在指定尺寸(size)的背景字符组成的大背景上。

保存图像时，默认亮度模式是黑板模式，前景白背景黑。使用反转模式的时候，使用白纸模式，背景白前景黑。前景背景字符的定义与亮度定义是分开的，互不相关。

# Options

+ -f FILENAME --filename FILENAME     :default tex.txt
+ -i NUMBER   --interval NUMBER       :default 1
+ -o NUMBER   --origin NUMBER         :default 1
+ -s NUMBER   --size NUMBER           :default 16
+ -r NUMBER   --row-number NUMBER     :default 16
+ -c NUMBER   --column-number NUMBER  :default 16
+ -x          --exchange-fb           :Exchange foreground and background
+ -a          --autogen               :Auto generate a batch of textiles

# Examples

```batch
texgenerator -f tex1.txt -i 3 -o 1 -s 16 -c 32 -r 64
texgenerator --filename tex2.txt --interval 6 --origin 3 --size 16 --column-number 32 --row-number 64
``````
