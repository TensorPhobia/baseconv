#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>
using namespace std;
/*
```
.SH SYNOPSIS
.B baseconv
.RI [ --help | --h ]
.RI [ -base " base " ]
.RI [ -bin | -dec | -hex | -oct ]
.I num
.RI [ --all | --bin | --dec | --hex | --oct | --(first char of desired output
bases concatenated) ]
```roff
*/

int main(int argc, char **argv) {
  // debuging
  /* for (int i = 0; i < argc; i++) {
      cout << "i = " << i << " argv =" << argv[i] << endl;
  } */
  // no arguments were supplied to the command
  if (argc == 1) {
    cerr << "Error: this command require at least one argument " << endl
         << "use --help or --h to see list of valid arguments" << endl;
    return 1;
  }

  /* all possible arguments length for the command
  baseconv +
  [ -bin | -dec | -hex | -oct ] num [ --all | --bin | --dec | --hex | --oct |
  --(first char of desired output bases concatenated) ] |     [ -base " base " ]
  num [ --all | --bin | --dec | --hex | --oct | --(first char of desired output
  bases concatenated) ] |            |         --help |            | | */
  if (argc != 4 && argc != 5 && argc != 2) {
    cerr << "Error: invalid arguments format " << endl
         << "use --help or --h to see list how to construct valid argument "
            "format"
         << endl;
    return 1;
  }

  if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--HELP") == 0 ||
      strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--H") == 0) {
    system("man baseconv");
    return 0;
  }

  long input = 0;

  /*
  bas
  bin
  dec
  hex
  oct
  */
  // handling custom base
  short offset = 0;
  if (strcmp(argv[1], "-base") == 0 || strcmp(argv[1], "-BASE") == 0 ||
      strcmp(argv[1], "-ba") == 0 || strcmp(argv[1], "-ba") == 0) {
    int customBase = 0;
    offset = 1;
    customBase = atoi(argv[2]);
    input = strtol(argv[3], nullptr, customBase);
  } else if (strcmp(argv[1], "-bin") == 0 || strcmp(argv[1], "-BIN") == 0 ||
             strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-B") == 0) {
    input = strtol(argv[2], nullptr, 2);
  } else if (strcmp(argv[1], "-dec") == 0 || strcmp(argv[1], "-DEC") == 0 ||
             strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "-D") == 0) {
    input = strtol(argv[2], nullptr, 10);
  } else if (strcmp(argv[1], "-hex") == 0 || strcmp(argv[1], "-HEX") == 0 ||
             strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-H") == 0) {
    input = strtol(argv[2], nullptr, 16);
  } else if (strcmp(argv[1], "-oct") == 0 || strcmp(argv[1], "-OCT") == 0 ||
             strcmp(argv[1], "-o") == 0 || strcmp(argv[1], "-O") == 0) {
    input = strtol(argv[2], nullptr, 8);
  } else {
    // throw an error no base is given
    cerr << "Error: no valid base is given " << endl
         << "use --help or --h to see list of valid bases" << endl;
    return 1;
  }

  /*
  all
  bin
  dec
  hex
  oct
  */

  if (strcmp(argv[3 + offset], "--all") == 0 ||
      strcmp(argv[3 + offset], "--ALL") == 0 ||
      strcmp(argv[3 + offset], "--a") == 0 ||
      strcmp(argv[3 + offset], "--A") == 0) {
    cout << "bin= " << bitset<CHAR_BIT * sizeof(input)>(input) << endl;
    cout << "dec= " << input << endl;
    cout << "hex= " << hex << input << endl;
    cout << "oct= " << oct << input << endl;

  } else if (strcmp(argv[3 + offset], "--bin") == 0 ||
             strcmp(argv[3 + offset], "--BIN") == 0 ||
             strcmp(argv[3 + offset], "--b") == 0 ||
             strcmp(argv[3 + offset], "--B") == 0) {
    cout << "bin= " << bitset<CHAR_BIT * sizeof(input)>(input) << endl;
  } else if (strcmp(argv[3 + offset], "--dec") == 0 ||
             strcmp(argv[3 + offset], "--DEC") == 0 ||
             strcmp(argv[3 + offset], "--d") == 0 ||
             strcmp(argv[3 + offset], "--D") == 0) {
    cout << "dec= " << input << endl;
  } else if (strcmp(argv[3 + offset], "--hex") == 0 ||
             strcmp(argv[3 + offset], "--HEX") == 0 ||
             strcmp(argv[3 + offset], "--h") == 0 ||
             strcmp(argv[3 + offset], "--H") == 0) {
    cout << "hex= " << hex << input << endl;
  } else if (strcmp(argv[3 + offset], "--oct") == 0 ||
             strcmp(argv[3 + offset], "--OCT") == 0 ||
             strcmp(argv[3 + offset], "--o") == 0 ||
             strcmp(argv[3 + offset], "--O") == 0) {
    cout << "oct= " << oct << input << endl;
  } else if (argv[3 + offset][0] == '-' && argv[3 + offset][1] == '-') {
    for (int i = 0; i < strlen(argv[3 + offset]); i++) {
      if (argv[3 + offset][i] == 'b') {
        cout << "bin= " << bitset<CHAR_BIT * sizeof(input)>(input) << endl;
      } else if (argv[3 + offset][i] == 'd') {
        cout << "dec= " << input << endl;
      } else if (argv[3 + offset][i] == 'h') {
        cout << "hex= " << hex << input << endl;
      } else if (argv[3 + offset][i] == 'o') {
        cout << "oct= " << oct << input << endl;
      }
    }
  } else {
    cerr << "Error: no valid base is given " << endl
         << "use --help or --h to see list of valid bases" << endl;
    return 1;
  }

  return 0;
}