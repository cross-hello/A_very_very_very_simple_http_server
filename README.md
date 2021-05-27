### Introduction
A very very very simple http server which could be used to dissect how http traffic happens between server and client.

### Compile

#### Linux
```shell
gcc -o http http.c
```
#### Windows
```shell
gcc -o http http.c  -lWs2_32
```

### Usage
#### Linux
```shell
./http 8080 index_.html
#Here 8080 is the port server will listen on
#index.html is the html file you want server to host
```
#### Windows
```shell
http.exe 8080 index.html
```

### Test

Open web browser, type in your ip address with port number you type above.

![Screenshot from 2021-05-27 10-32-14](Screenshot%20from%202021-05-27%2010-32-14.png)

