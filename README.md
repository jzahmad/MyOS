This C code implements a simple shell-like program. It allows users to execute commands, view their command history, and
repeat previously executed commands. The code utilizes standard C libraries like `stdio.h`, `stdlib.h`, `string.h`, and
`unistd.h` for input/output, memory management, string manipulation, and system calls, respectively. The program defines
a `History` struct to store command details (PID and command string) and maintains a history array. It uses `fork()` to
create child processes for executing commands, `execvp()` to replace the child's process image with the command, and
`wait()` to wait for the child process to finish. The code handles special commands like "history", "!!", and "exit",
allowing users to view their history, repeat the most recent command, or exit the program.
