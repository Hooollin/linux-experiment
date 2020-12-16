ATTENTION!!!
g++ -fpic --shared function.cpp IPrintPlugin.cpp

--shared 必须在前面，function.cpp 必须在IPrintPlugin.cpp前面

https://stackoverflow.com/questions/18827938/strange-g-linking-behavior-depending-on-arguments-order

g++ -fpic --shared function.cpp IPrintPlugin.cpp -L.
链接的时候对文件的顺序有要求
-L 搜索当前目录下的文件


