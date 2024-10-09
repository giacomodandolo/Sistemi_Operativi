#!/bin/bash

# Number of logins(s) of a specifi user

echo -n "String: "
read word

l=$(echo -n $word | wc -c)

echo "Word $word is $l character long"

exit 0
