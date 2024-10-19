// RTD2020UserFwFolderNameStringTable.h
// First Byte shall be the number of Folder Name char. A valid number of File Name should be 26 or less.
// Second Byte shall be 1 if there's any ' ' (SPACE) exist in the file name, and shall be 0 if there's not.
// For Example : RTK_MM_PROGRAM.bin (number of char is 18, and no SPACE exist)
    13, 0,
    'R', 'T', 'K',
    '_', 'M', 'M',  '_',
    'F', 'O', 'L',  'D',
    'E', 'R',