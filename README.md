# RISC-V LCD1602/LCD2004
LCD1602 Example Code for RISC-V MCUs CH32Vxxx

Tested witn CH32V103 and LCD1602 and LCD2004 - 4 bit parrallel I/F
should run on all CH32Vxxx ( and probably CH32Fxxx )

hack of the Arduino LiquidCrystal library.

To Install follow steps 1 - 3 on the <a href=https://github.com/CanHobby/RISC-V>How-To</a> to set up a fresh workspace then..

1). copy main.c and the LCD subdirectory into the User directoty of your MRS User directory overwriting where necessary.

2). copy all the files from this Peripheral directory - including the "inc" subdirectory to the Peripheral directory on your MRS.

.... do a build project and then hit F8 to upload to your board.
