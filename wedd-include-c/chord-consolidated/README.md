**CMSI 284** Computer System Organization/Systems Programming, Spring 2020

# Chord Consolidated
Finally, the moment many of you have been waiting for—consolidating the functions written for “Oh Say Can You C” into a single file, to be shared with all of the programs that you wrote!

## What to Do
There shouldn’t be any new code to write for this section; just some rearranging (and a lot of deleting!):

1. Move your `split_string_at_index` implementation to _string-plus.c_ (joining `is_non_negative_numeral` as an addition to our own collection of reusable string functions)
2. Move all chord-related implementations to _notes.c_
3. All of your programs should be left with just the `main` and any helper functions written _specifically_ for those programs (i.e., not needed by the chord-related “public” functions)

The _notes.h_ file has been revised in this assignment to accommodate this move, so keep that untouched. In addition, a _string-plus.h_ file has been created to accompany the new _string-plus.c_ file.

After these changes, your _split-string-at-index.c_ program should now compile this way:

    gcc string-plus.c split-string-at-index.c

All chord-related programs should now compile this way:

    gcc string-plus.c notes.c <file-with-main-function.c>

The resulting _a.out_’s should then behave exactly like your current implementations.

Note that this assignment is _solely_ about correct code consolidation. If your implementations have bugs, then those bugs will not result in deductions in this assignment. You are being graded on correct _restructuring_ for this one; the previous assignment covers actual functionality.

## Specific Point Allocations
This portion of the assignment is scored according to outcomes _3a_, _4a_, and _4b_ in the [syllabus](https://dondi.lmu.build/spring2020/cmsi284/cmsi284-spring2020-syllabus.pdf). For this particular assignment, graded categories are as follows:

| Category | Points | Outcomes |
| -------- | -----: | -------- |
| Consolidated code compiles and runs as specified | 6 | _3a_, _4a_ |
| All shared/“public” functions are defined only once across all files | 4 | _4b_ |
| **Total** | **10** |

Note that inability to compile and run to begin with will negatively affect the correctness of program output and proper handling of invalid user input.

