# ACBTool

libraries for working with Adobe's Colorbook file format (.acb). Written by Spike Grobstein (spikegrobstein@mac.com)

This is very much a work in progress. I cranked this code out over a weekend back in like 2007 and never finished it. My goal was to create a full library for working with acb files based on the file format described by Ates Goral (http://magnetiq.com/docs/PhotoshopColorBook.txt).

As of 2010/11, I have not yet configured autotools or organized the sourcecode. I may sit down when I have some free time and clean
up the code for public consumption.

## Building

To build the software, run the make.sh command (included in this archive). it will output a commandline program called `acbtool`

This should build on any POSIX operating system (OSX, Linux, BSD, maybe cygwin?, etc) without modification.

## Acknowledgements

This software is based on documentation by Ates Goral (http://magnetiq.com)