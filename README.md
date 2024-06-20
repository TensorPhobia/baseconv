
![Logo](./assets/logo.png)


## Description
`baseconv` is a command-line utility that converts numbers between different numerical bases, including binary, decimal, hexadecimal, and octal.

## Features

- Input can be in any base including iregular ones eg: base 3 up to base 32
- Output converstion can be to all regular bases
- Output can be customized 
- Cross platform
- Quick and responsive
- Includes a man page as well as a --help flag to demonstrate how to build a command  
- Includes an installation bash script to allow you to use the command anywhere on your computer



## Installation

Install baseconv auto installation script via

```bash
 $ sudo ./install.sh
```

## Usage/Examples

```bash
$ baseconv -bin 101011 --dho
dec= 43
hex= 2b
oct= 53
```
this command will interpret 1010111 in binary and output the result in all common bases

## Documentation
for documentation use 
```bash
$ baseconv --help
```
or alternatively
 ```bash
$ man baseconv
```

## Roadmap

- Add twos compliment support

- Add colored output to distinguish number from sign 


## Used By

This project orginally created so I can cheat through the assignements so I guess
I can quote my university lmafo:

- [ISI Ariana](http://www.isi.rnu.tn/)
- [université tunis el manar](http://www.utm.rnu.tn/utm/fr/)


## Contributing
Visit the project's GitHub page for contributions and bug reports: [baseconv](https://github.com/TensorPhobia/baseconv)
Contribute to development and help improve the utility..


## Author

written by [@TensorPhobia](https://www.github.com/TensorPhobia)


## License
This is free software; see the source for copying conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
