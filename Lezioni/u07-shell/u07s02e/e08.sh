#!/bin/bash

(( 0 && 1 )) # Logical AND
echo $? # 1 ***
# And so ...
let "num = (( 0 && 1 ))"
echo $num # 0
# But ...
let "num = (( 0 && 1 ))"
echo $? # 1 ***
(( 200 || 11 )) # Logical OR
echo $? # 0 ***

# ...
let "num = (( 200 || 11 ))"
echo $num # 1
let "num = (( 200 || 11 ))"
echo $? # 0 ***
(( 200 | 11 )) # Bitwise OR
echo $? # 0 ***
# ...
let "num = (( 200 | 11 ))"
echo $num # 203
let "num = (( 200 | 11 ))"
echo $? # 0 ***
# The "let" construct returns the same exit status
#+ as the double-parentheses arithmetic expansion.
var=-2 && (( var+=2 ))
echo $? # 1
var=-2 && (( var+=2 )) && echo $var
# Will not echo $var!

if cmp a b &> /dev/null # Suppress output.
then echo "Files a and b are identical."
else echo "Files a and b differ."
fi
# The very useful "if-grep" construct:
# -----------------------------------
if grep -q Bash file
then echo "File contains at least one occurrence of Bash."
fi
word=Linux
letter_sequence=inu
if echo "$word" | grep -q "$letter_sequence"
# The "-q" option to grep suppresses output.
then
echo "$letter_sequence found in $word"
else
echo "$letter_sequence not found in $word"
fi
if COMMAND_WHOSE_EXIT_STATUS_IS_0_UNLESS_ERROR_OCCURRED
then echo "Command succeeded."
else echo "Command failed."
fi

#!/bin/bash
# Tip:
# If you're unsure how a certain condition might evaluate,
#+ test it in an if-test.
echo
echo "Testing \"0\""
if [ 0 ] # zero
then
echo "0 is true."
else # Or else ...
echo "0 is false."
fi # 0 is true.
echo

echo "Testing \"1\""
if [ 1 ] # one
then
echo "1 is true."
else
echo "1 is false."
fi # 1 is true.
echo
echo "Testing \"-1\""
if [ -1 ] # minus one
then
echo "-1 is true."
else
echo "-1 is false."
fi # -1 is true.
echo
echo "Testing \"NULL\""
if [ ] # NULL (empty condition)
then
echo "NULL is true."
else
echo "NULL is false."
fi # NULL is false.
echo
echo "Testing \"xyz\""
if [ xyz ] # string
then
echo "Random string is true."
else
echo "Random string is false."
fi # Random string is true.
echo
echo "Testing \"\$xyz\""
if [ $xyz ] # Tests if $xyz is null, but...
# it's only an uninitialized variable.
then
echo "Uninitialized variable is true."
else
echo "Uninitialized variable is false."
fi # Uninitialized variable is false.
echo
echo "Testing \"-n \$xyz\""
if [ -n "$xyz" ] # More pedantically correct.
then
echo "Uninitialized variable is true."
else
echo "Uninitialized variable is false."
fi # Uninitialized variable is false.
echo
xyz= # Initialized, but set to null value.
echo "Testing \"-n \$xyz\""
if [ -n "$xyz" ]
then
echo "Null variable is true."
else
echo "Null variable is false."
fi # Null variable is false.
echo
# When is "false" true?
echo "Testing \"false\""
if [ "false" ] # It seems that "false" is just a string ...
then
echo "\"false\" is true." #+ and it tests true.
else
echo "\"false\" is false."
fi # "false" is true.
echo
echo "Testing \"\$false\"" # Again, uninitialized variable.
if [ "$false" ]
then
echo "\"\$false\" is true."
else
echo "\"\$false\" is false."
fi # "$false" is false.
# Now, we get the expected result.
# What would happen if we tested the uninitialized variable "$true"?
echo
exit 0
