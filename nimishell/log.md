- printf("%sI'm here%s\n", COLOR_YELLOW, COLOR_RESET);
	
---------------------------------
TODO: put protect for open function in redir
TODO: Check leaks in non interactive mode and interactive exit
TODO: Include cmd_list in executer to get all the arguments of the command
TODO: Include a break in executer when cd is used in multiple pipes. It should work just when it is alone, but show error messages in the path if invalid
TODO: Fix expanser with 2 consecutive variables without space in the middle
TODO: Fix expanding with not found variables to return null




---------------------------------

DONE~~: is expand in expanser, "$*" doesn't work and "$0" gets open input~~
DONE~~: remove quotes in case quotes are not edge (not"HOME", but $$"HOME")~~
DONE~~: control {} in expanser~~
DONE~~: put builtins's exit in sig_eof ~~
DONE~~: make simpletest(unset)~~
DONE~~: expanser: "$USER"'$USER' doesn't work~~
DONE~~: make lexer and expanser works~~





---------------------------------
*** CASES which should control ***
~~bash-3.2$ cd $$HOME~~
~~bash: cd: 4180HOME: No such file or directory~~230811
bash-3.2$ cat < file1 | grep a | wc -l > file2 > file3
bash-3.2$ export hi1 hi2 "hi3 hi4"|ls -----> export will not work, but only ls (in bash)
bash-3.2$ cat < log.md |cat >> log.md 
bash-3.2$ echo $
bash-3.2$ env | grep -v -E '^_=' | sort
export | grep -v -E '^declare -x _='





