#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
using namespace std;
#define FRACTION_PRECISION 30

/*
```
.SH SYNOPSIS
.B baseconv
.RI [ --help -he ]
.RI [ -base " base " ]
.RI [ --bin -b | --dec -d | --hex -h | --oct -o ]
.I num
.RI [ --all -a | --bin -b | --dec -d | --hex -h | --oct -o | -(first char of
desired output bases concatenated) ]
```roff
*/

//=========================[atoi with any base]==============================
double parseNumber(char *str, int base) {
  double res = 0.0f;
  bool encountredPoint = false;
  double negativePower = 1.0 / base;
  short sign = 1;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == ',' || str[i] == '.') {
      encountredPoint = true;
      continue;
    }
    if (str[i] == '-') {
      sign *= -1;
    }
    if (isdigit(str[i])) {
      if (encountredPoint) {
        res += (str[i] - '0') * negativePower;
        negativePower *= 1.0 / base;
      } else {
        res = res * base + (str[i] - '0');
      }
    } else if (isalpha(str[i])) {
      if (encountredPoint) {
        res += (toupper(str[i]) - 55) * negativePower;
        negativePower *= 1.0 / base;
      } else {
        res = res * base + (toupper(str[i]) - 55);
      }
    }
  }
  /*If no point found make output precision 0*/

  return res * sign;
}
//=========================[atoi with any base]==============================

//=========================[Sanitizers]==============================
// Function to check if a string is empty or contains only '.' or ','
bool isStringEmptyOrContainsOnlyPoint(string str) {
  return str.empty() || str == "." || str == ",";
}

// Function to check if a string contains more than one '.' or ','
int containMultiplePoints(string str) {
  int points_count = 0;
  for (int i = 0; i < str.length(); i++) {
    char ch = str[i];
    if (ch == '.' || ch == ',') {
      points_count++;
    }
    if (points_count > 1) {
      return i; // Return the position of the multiple point
    }
  }
  return -1; // No multiple points found
}

// Function to find the position of an invalid digit in the given base
int findInvalidDigitPosition(string str, int base) {
  for (int i = 0; i < str.length(); i++) {
    char ch = str[i];
    if (isalnum(ch) || ch == '.' || ch == ',' || ch == '-') {
      if (isdigit(ch) && (ch - '0' >= base)) {
        return i; // Return the position of the invalid digit
      } else if (isalpha(ch) && (toupper(ch) - 'A' + 10 >= base)) {
        return i; // Return the position of the invalid digit
      }
    } else {
      return i; // Return the position of the invalid digit
    }
  }
  return -1; // No invalid digit found
}

// Function to sanitize input string for base and number validity
bool sanitizeInput(string num, int base) {
  if (isStringEmptyOrContainsOnlyPoint(num)) {
    cerr << "Error: The number cannot be empty or contain only '.' or ','"
         << endl;
    return false;
  }

  int multiplePointPos = containMultiplePoints(num);
  if (multiplePointPos != -1) {
    cerr << "Error: The number contains multiple points at position "
         << multiplePointPos << endl;
    cerr << "Please make sure the number contains at most one '.' or ','"
         << endl;
    return false;
  }

  int invalidDigitPos = findInvalidDigitPosition(num, base);
  if (invalidDigitPos != -1) {
    cerr << "Error: Invalid digit '" << num[invalidDigitPos]
         << "' found in the number" << endl;
    cerr << num << endl;
    cerr << string(invalidDigitPos, ' ') << "^" << endl;
    cerr << string(invalidDigitPos, ' ') << "|" << endl;

    if (base <= 10) {
      cerr << "Please make sure your number digits are in the range [0, "
           << base - 1 << "] inclusive" << endl;
    } else {
      char maxChar = 'A' + (base - 10 - 1); // 'A' + (base - 10) - 1
      cerr << "Please make sure your number digits are in the range [0, "
           << maxChar << "] inclusive" << endl;
    }
    return false;
  }

  return true; // Input is valid
}
//=========================[Sanitizers]==============================

//=========================[Base 10 to any base]==============================
string convertToBase(double x, int base) {
  int sign = signbit(x) ? -1 : 1;
  x *= sign;
  int expo = x;
  double fract = x - expo;
  string str;
  int div;
  int rest;
  do {
    div = expo / base;
    rest = expo % base;
    expo = div;
    if (rest <= 9) {
      str.push_back(rest + '0');
    } else {
      str.push_back('A' + (rest - 10));
    }
  } while (div > 0);
  reverse(str.begin(), str.end()); // construct exponent part of the answer

  if (fract > 0.0) {
    str.push_back('.');
    int precision = FRACTION_PRECISION;
    do {
      fract *= base;
      precision--;
      if (((int)fract) <= 9) {
        str.push_back(((int)fract) + '0');
      } else {
        str.push_back('A' + (((int)fract) - 10));
      }
      fract = fract - (int)(fract);
    } while (precision > 0 && fract > 0);
  }

  if (sign < 0) {
    str.insert(str.begin(), '-');
  }
  return str;
}
//=========================[Base 10 to any base]==============================

int main(int argc, char **argv) {
  // debuging
  /* for (int i = 0; i < argc; i++) {
    cout << "i = " << i << " argv =" << argv[i] << endl;
  } */
  // no arguments were supplied to the command
  if (argc == 1) {
    cerr << "Error: this command require at least one argument " << endl
         << "use --help or -he to see list of valid arguments" << endl;
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
         << "use --help or -h to see list how to construct valid argument "
            "format"
         << endl;
    return 1;
  }

  if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--HELP") == 0 ||
      strcmp(argv[1], "-he") == 0 || strcmp(argv[1], "-HE") == 0) {
    system("man baseconv");
    return 0;
  }

  double input = 0;

  /*
  bas
  bin
  dec
  hex
  oct
  */
  // handling custom base
  short offset = 0;
  if (strcmp(argv[1], "--base") == 0 || strcmp(argv[1], "--BASE") == 0 ||
      strcmp(argv[1], "-ba") == 0 || strcmp(argv[1], "-BA") == 0) {
    int customInputBase = 0;
    offset = 1;
    customInputBase = atoi(argv[2]);
    // handling invalid bases
    if (customInputBase < 2 || customInputBase > 32) {
      cerr << "Error: invalid input base given " << endl
           << "please make sure your base is in range [2,32] inclusive" << endl;
      return 1;
    }

    if (!sanitizeInput(argv[2 + offset], customInputBase)) {
      return 1;
    }

    input = parseNumber(argv[3], customInputBase);
  } else if (strcmp(argv[1], "--bin") == 0 || strcmp(argv[1], "--BIN") == 0 ||
             strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-B") == 0) {

    if (!sanitizeInput(argv[2], 2)) {
      return 1;
    }

    input = parseNumber(argv[2], 2);
  } else if (strcmp(argv[1], "--dec") == 0 || strcmp(argv[1], "--DEC") == 0 ||
             strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "-D") == 0) {

    if (!sanitizeInput(argv[2], 10)) {
      return 1;
    }

    input = parseNumber(argv[2], 10);
  } else if (strcmp(argv[1], "--hex") == 0 || strcmp(argv[1], "--HEX") == 0 ||
             strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-H") == 0) {

    if (!sanitizeInput(argv[2], 16)) {
      return 1;
    }

    input = parseNumber(argv[2], 16);
  } else if (strcmp(argv[1], "--oct") == 0 || strcmp(argv[1], "--OCT") == 0 ||
             strcmp(argv[1], "-o") == 0 || strcmp(argv[1], "-O") == 0) {

    if (!sanitizeInput(argv[2], 8)) {
      return 1;
    }

    input = parseNumber(argv[2], 8);
  } else {
    // throw an error no base is given
    cerr << "Error: no valid base is given " << endl
         << "use --help or -he to see list of valid bases" << endl;
    return 1;
  }

  /*
  all
  bin
  dec
  hex
  oct
  */
  // cout << fixed;
  if (strcmp(argv[3 + offset], "--all") == 0 ||
      strcmp(argv[3 + offset], "--ALL") == 0 ||
      strcmp(argv[3 + offset], "-a") == 0 ||
      strcmp(argv[3 + offset], "-A") == 0) {
    cout << "bin= " << convertToBase(input, 2) << endl;
    cout << "dec= " << input << endl;
    cout << "hex= " << convertToBase(input, 16) << endl;
    cout << "oct= " << convertToBase(input, 8) << endl;

  } else if (strcmp(argv[3 + offset], "--bin") == 0 ||
             strcmp(argv[3 + offset], "--BIN") == 0 ||
             strcmp(argv[3 + offset], "-b") == 0 ||
             strcmp(argv[3 + offset], "-B") == 0) {
    cout << "bin= " << convertToBase(input, 2) << endl;
  } else if (strcmp(argv[3 + offset], "--dec") == 0 ||
             strcmp(argv[3 + offset], "--DEC") == 0 ||
             strcmp(argv[3 + offset], "-d") == 0 ||
             strcmp(argv[3 + offset], "-D") == 0) {
    cout << "dec= " << input << endl;
  } else if (strcmp(argv[3 + offset], "--hex") == 0 ||
             strcmp(argv[3 + offset], "--HEX") == 0 ||
             strcmp(argv[3 + offset], "-h") == 0 ||
             strcmp(argv[3 + offset], "-H") == 0) {
    cout << "hex= " << convertToBase(input, 16) << endl;
  } else if (strcmp(argv[3 + offset], "--oct") == 0 ||
             strcmp(argv[3 + offset], "--OCT") == 0 ||
             strcmp(argv[3 + offset], "-o") == 0 ||
             strcmp(argv[3 + offset], "-O") == 0) {
    cout << "oct= " << convertToBase(input, 8) << endl;
  } else if (argv[3 + offset][0] == '-') {
    for (int i = 0; i < strlen(argv[3 + offset]); i++) {
      if (argv[3 + offset][i] == 'b') {
        cout << "bin= " << convertToBase(input, 2) << endl;
      } else if (argv[3 + offset][i] == 'd') {
        cout << "dec= " << input << endl;
      } else if (argv[3 + offset][i] == 'h') {
        cout << "hex= " << convertToBase(input, 16) << endl;
      } else if (argv[3 + offset][i] == 'o') {
        cout << "oct= " << convertToBase(input, 8) << endl;
      } else if (argv[3 + offset][i] == '-') {
        continue;
      } else {
        string num;
        for (int lastNumberFound = i;
             lastNumberFound < strlen(argv[3 + offset]); lastNumberFound++) {
          if (isdigit(argv[3 + offset][lastNumberFound])) {
            num.push_back(argv[3 + offset][lastNumberFound]);
          } else {
            break;
          }
        }
        if (!num.empty()) {
          int customOutputBase = stoi(num);
          i += num.size(); // susy needs maths
          //debuging
          //cout << "num = " << num << endl;
          if (customOutputBase < 2 || customOutputBase > 32) {
            cerr << "Error: invalid ouput base given aka (" << customOutputBase
                 << ')' << endl
                 << "please make sure your base is in range [2,32] inclusive"
                 << endl;
            return 1;
          }
          cout << "base" << customOutputBase << "= "
               << convertToBase(input, customOutputBase) << endl;
        }
      }
    }
  } else {
    cerr << "Error: no valid out base is given " << endl
         << "use --help or -he to see list of valid bases" << endl;
    return 1;
  }

  return 0;
}