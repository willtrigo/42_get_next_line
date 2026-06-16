*This project has been created as part of the 42 curriculum by dande-je.*

# ⤷ 42sp - Get next line

<picture>
	<img alt="Get next line" src="img/42_get_next_line.png">
</picture>
<picture >
	<img alt="OS" src="https://img.shields.io/badge/Linux-OS?&label=OS&labelColor=gray&color=dodgerblue">
</picture>
<picture >
	<img alt="Language" src="https://img.shields.io/badge/C-Language?&label=Language&labelColor=gray&color=dodgerblue">
</picture>
<picture >
	<img alt="Status" src="https://img.shields.io/badge/Completed-Status?&label=Status&labelColor=gray&color=green">
</picture>

## Description

The **get_next_line** project is a fundamental project from the 42 curriculum. It consists of implementing a function that reads a line from a file descriptor, one line at a time, without knowing the file size in advance.

The function must:
- Return the line including the terminating `\n` (except at EOF when there's no newline)
- Handle multiple file descriptors simultaneously
- Be memory efficient
- Work with `read()`, `malloc()` and `free()`

This project is an excellent exercise for understanding **static variables**, memory management, and efficient file reading in C.

## Algorithm Explanation

The chosen implementation uses a **linked list per file descriptor** to accumulate characters until a newline is found. Each file descriptor maintains its own state through a static array of `t_file` structures.

**Why this approach?**
- Allows safe handling of multiple file descriptors at once (mandatory for the bonus)
- Avoids large buffer reallocations
- Clean separation between reading raw data and building the final string
- Easy memory cleanup on errors

The reading process works as follows:
1. Use a static buffer to read chunks of data (`BUFFER_SIZE`)
2. Store each character in a linked list (`history`)
3. When `\n` is found, convert the list into a null-terminated string and free the nodes
4. Maintain cursor position for the next read

## Instructions

### Compilation

```sh
# Mandatory part
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```
```sh
# Or with custom buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 get_next_line.c get_next_line_utils.c -o gnl
```
```sh
# Bonus part
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```
```sh
# Or with custom buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

## Usage Example

When compiling `get_next_line` or its **bonus** version, be sure to include the following flags

```sh
c
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Resources

- 42 Project Subject (PDF)
- [GNU C Library - File I/O](https://www.gnu.org/software/libc/manual/html_node/File-I-O.html)
- [man pages for read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)

## AI Usage

AI (Claude and Grok) was used in the following parts:

- Refactoring the name of some variables for better structure and readability
- Adding professional **Doxygen** documentation across all files
- Improving and updating this `README.md` to comply with the latest 42 requirements
