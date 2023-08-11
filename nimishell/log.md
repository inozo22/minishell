- printf("%sI'm here%s\n", COLOR_YELLOW, COLOR_RESET);
	
-----------------------------------------------------------------------
TODO: make lexer and expanser works
TODO: remove quotes in case quotes are not edge (not"HOME", but $$"HOME")
TODO: obtain file name in parser(?)


-----------------------------------------------------------------------
DONE~~: is expand in expanser, "$*" doesn't work and "$0" gets open input~~





-----------------------------------------------------------------------
*** CASES which should control ***
~~bash-3.2$ cd $$HOME~~
~~bash: cd: 4180HOME: No such file or directory~~230811
bash-3.2$ cat < file1 | grep a | wc -l > file2 > file3
bash-3.2$ export hi1 hi2 "hi3 hi4"|ls -----> export will not work, but only ls


