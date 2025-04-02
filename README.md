# pipex
This project is about pipes management.

## Program execution
To run the program, first compile it with `make`. Then: 
```{bash}
./pipex file1 command1 command2 file2
```

## Requisites
The program must do the same as the following command:
```{bash}
< file1 command1 | command2 > file2
```

`file1` and `file2` are filenames.

`command1` and `command2` are shell commands with their respective parameters.

### Examples
`./pipex infile "ls -l" "wc -l" outfile` = `< infile ls -l | wc -l > outfile`

`./pipex infile "grep a1" "wc -w" outfile` = `< infile grep a1 | wc -w > outfile`

## Bonus
1. Manage multiple pipes:
	```{bash}
	./pipex file1 command1 command2 command3 commandN file2
	```
	should do the same as
	```{bash}
	< file1 command1 | command2 | command3 | commandN > file2
	```

2. Accept `<<` and `>>` when the 1st parameter is here_doc:
	```{bash}
	./pipex here\_doc DELIMITER command1 command2 file
	```
	should do the same as
	```{bash}
	command1 << DELIMITER | command2 >> file2
	```


## Authorized functions
| function | function desc | use I give it |
|-|-|-|
| open | opens a file |-|
| close | closes a fd |-|
| read | reads bytes from a fd |-|
| write | writes into a fd |-|
| malloc | allocates memory |-|
| free | frees memory |-|
| perror | prints a message and errno in stderror |-|
| strerror | translates errnum |-|
| access | checks if the proccess can access a file |-|
| dup | duplicates an fd into the lowest unused fd |-|
| dup2 | duplicates an fd into the specified fd |-|
| execve | executes a program |-|
| exit | terminates a proccess |-|
| fork | creates a child proccess |-|
| pipe | creates a pipe (unidirectional data channel for interprocess communication) |-|
| unlink | deletes a name from the filesystem |-|
| wait | makes the current theard wait until one of its children terminates |-|
| waitpid | makes the current theard wait until a specified child changes its state |-|

## Helpful resources
- Heredoc (<<)
	- https://askubuntu.com/a/678919
