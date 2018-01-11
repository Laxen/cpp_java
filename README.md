# cpp_java

Compile and run using the following commands

```
g++ -g -I/usr/lib/jvm/java-8-openjdk-amd64/include/ -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux/ -L/usr/bin/java -L/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/ main.cc -ljvm

LD_LIBRARY_PATH=/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server ./a.out
```
