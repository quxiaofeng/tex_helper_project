# Fuction

This command is used to convert a tex pattern file to a image file.

# Options

+ -s FILENAME      --source-filename FILENAME       :default tex.txt
+ -d NUMBER        --display-factor NUMBER   :default 4
+ -b "CHARACTER"   --background-char "CHARACTER"       :default " "(blank)
+ -f "CHARACTER"   --foreground-char "CHARACTER"       :default X
+ -o FILENAME      --object-filename FILENAME

Examples:

```batch
textile2image -s tex1.txt -d 4 -f "X" -b " " -o tex1.png
textile2image --source-filename tex1.txt --display-factor 4 --foreground-char "X" --background-char " " --object-filename tex1.png
``````
