#include <stdlib.h>
#include <stdio.h>

// Our version of emit_byte just sends it straight to standard output.
void emit_byte(int encoded_byte) {
    putchar(encoded_byte);
}

// This is a C implementation of Dr. Toal’s to_utf_8 function from
//     https://cs.lmu.edu/~ray/notes/charenc/
//
// It has been renamed “emit_utf_8” to indicate that it doesn’t return
// the encoded code point as the function’s result; instead, it sends
// the encoding out one byte at a time.
void emit_utf_8(int code_point) {
    if (code_point > 0x10FFFF) {
        // If the code point is too large, we display it in hex and report that it is too large.
        printf("(%08X code point is too large)", code_point);
    } else if (code_point <= 0x7F) {
        emit_byte(code_point);
    } else if (code_point <= 0x7FF) {
        emit_byte(0xC0 | (code_point >> 6));
        emit_byte(0x80 | (code_point & 0x3F));
    } else if (code_point <= 0xFFFF) {
        emit_byte(0xE0 | (code_point >> 12));
        emit_byte(0x80 | ((code_point >> 6) & 0x3F));
        emit_byte(0x80 | (code_point & 0x3F));
    } else {
        emit_byte(0xF0 | (code_point >> 18));
        emit_byte(0x80 | ((code_point >> 12) & 0x3F));
        emit_byte(0x80 | ((code_point >> 6) & 0x3F));
        emit_byte(0x80 | (code_point & 0x3F));
    }
}

// ***** CHANGE THIS SO THAT BEHAVES AS DESCRIBED IN THE INSTRUCTIONS. *****
int main(int argc, char** argv) {
    // Check for the correct number of arguments.
    if (argc < 2) {
        puts("This program requires one or more command line arguments,");
        puts("one for each code point to encode as UTF-8.");
        return 1;
    }

    int code_point;
    int successful_scans;
    char* code_point_string;

    // Feel free to look up the sscanf function to get a full understanding of what it’s doing.
    for (int i = 1; i < argc; i++) {
        code_point_string = argv[i];
        successful_scans = sscanf(code_point_string, "U+%6X", &code_point);

        if (successful_scans == 1) {
            emit_utf_8(code_point);
        } else {
            printf("(%s incorrect format)", code_point_string);
        }
    }

    // puts is printf’s simpler cousin, and it automatically prints a newline to boot.
    puts("");
    return 0;
}
