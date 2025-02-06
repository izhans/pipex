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
| open |-|-|
| close |-|-|
| read |-|-|
| write |-|-|
| malloc |-|-|
| free |-|-|
| perror |-|-|
| strerror |-|-|
| access |-|-|
| dup |-|-|
| dup2 |-|-|
| execve |-|-|
| exit |-|-|
| fork |-|-|
| pipe |-|-|
| unlink |-|-|
| wait |-|-|
| waitpid |-|-|

## Helpful resources
- Heredoc (<<)
	- https://askubuntu.com/a/678919
