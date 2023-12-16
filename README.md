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

##

The **get_next_line** project is a fundamental project that aims to develop a function capable of reading a line from a file descriptor. It allows you to retrieve the next line from a file, one line at a time, without reading the entire file at once. The function is designed to be memory efficient and work seamlessly with multiple file descriptors.

## Usage

When compiling `get_next_line` or its **bonus** version, be sure to include the following flags

```sh
$ gcc -Wall -Wextra -Werror -D BUFFER_SIZE=xxx <files>.c
```

Where the `xxx` can be substituted by the number of bytes read at a time into the buffer for the `read` function.
