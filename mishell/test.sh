#!/bin/bash

echo -e "cd ..\n pwd" | ./minishell > minishell.txt
echo -e "cd ..\n pwd" | bash > bash.txt
diff minishell.txt bash.txt