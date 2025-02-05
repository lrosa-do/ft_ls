# ft_ls

## Description
This project aims to recreate the behavior of the original `ls` command while adhering to the following constraints and variations.

## Required Features
- The implementation must support the following options:
  - `-l` (Long format listing)
  - `-R` (Recursive listing)
  - `-a` (Include hidden files)
  - `-r` (Reverse order)
  - `-t` (Sort by modification time)

- Consider the implications of the `-R` option from the beginning of the implementation.
- The output format must closely match that of the system `ls` command.

## Exclusions
- **Column formatting** is not required when `-l` is **not** specified.
- **ACL (Access Control Lists) and extended attributes** are not required.

## Evaluation Criteria
- The output must remain as **identical as possible** to the original `ls`, including spacing and alignment.
- Padding and pagination will be graded with flexibility, but all required information must be displayed correctly.

