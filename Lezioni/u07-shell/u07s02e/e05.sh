#!/bin/bash

# Sum of product

echo -n "Reading n1: "
read n1
echo -n "Reading n2: "
read n2

let s=n1+n2
let p=n1*n2

echo "Sum: $s"
echo "Product: $p"

exit 0
