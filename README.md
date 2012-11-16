# Textile Helper Project

把不同的纹样编织到一起

# Design 设计

+ 所有功能都是由Textile类实现。
+ AnyOption用来解析命令行参数。

依赖

+ Qt 4.8.1 （QtSDK 1.2.1 更新）和 MSVC 2010。
其实没有依赖于平台的代码，只是没有在其他平台上测试。
+ OpenCV 2.4.2 动态库，自行编译，依赖于以上平台(qt481 msvc2010 x86)

+ QtSDK [下载地址](http://www.developer.nokia.com/info/sw.nokia.com/id/da8df288-e615-443d-be5c-00c8a72435f8/Qt_SDK.html)。或者可以选择[更新的版本](http://qt-project.org/downloads)。
+ OpenCV 库已经提供，但也可以[下载源码](http://opencv.org/downloads.html)自行编译。

# Structure 结构

+ **texgenerator** 用来生成pattern，使用方法见其README.md
+ **texhelper** 用来编织patterns，使用方法见其README.md
+ **libs** 依赖的qt481库和opencv242库文件。还需要有QtSDK和Microsoft VC2010。
+ **test** 测试相关程序的脚本
+ **planOne** 实现方案一的程序
+ **planTwo** 实现方案二的程序

# Examples 样例

## A long exmaple

生成10个patterns并编织。

+ 演示根据指定起始点和间隔，生成纹样。
+ 演示添加多个模式到同一个纹样。
+ 演示编织许多（十个）纹样
+ 演示使用长格式参数使用生成(texgenerator)和编织(texhelper)命令

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
## A small exmaple

+ 演示使用短格式参数

```batch
texgenerator -f tex21.txt -i 5 -o 3 -s 16
texgenerator -f tex22.txt -i 6 -o 8 -s 16
texgenerator -f tex23.txt -i 9 -o 6 -s 16
texhelper -n 3 -s 16 tex21.txt tex22.txt tex23.txt -o texWeaveMini.txt
``````
