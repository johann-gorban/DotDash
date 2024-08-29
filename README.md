# DotDash. Morse translator

## Why DotDash?
* Minimalistic & Multiplatform.
* Incredibly fast algorithm.
* Rounded corners everywhere.

DotDash is what you really want to use to translate morse. Forget about web-freezes and high RAM-using. Just translate

### The project tree 
```
.
├── README.md
├── include
│   ├── activation.h
│   ├── alphabet.h
│   └── callbacks.h
├── main.c
├── meson.build
└── source
    ├── activation.c
    ├── alphabet.c
    └── callbacks.c
```
### How to build it?
It's pretty easy to build thanks to Meson. You have to run three commands:
```
meson setup build
meson compile -C build
./build/app
```

### You know how to improve it?
You can bring improvements into it and help me as a student. All you need is just your ideas' description or code examples. Write me an e-mail with subject "DotDash improvements".

This project is made with educational purpose. 
