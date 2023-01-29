# srv-scan
The simplest TCP server scanner
## Features
* Super fast
* Easy to use
* Lightweight
## Building
### Requirements
* Make
* GCC

To build srv-scan run `make` in the root of this project. The produced binary will be located under the `build/` directory.
## Using srv-scan
`build/srv-scan 256 22 1000`

This will scan port 22 with 256 threads and a timeout of 1 second.

* Replace the first argument with the number of threads you want to scan with ( 1 - 256 )
* Replace the second argument with the port you want to scan ( 0 - 65535 )
* Replace the third argument with the timeout for the port to send a response ( in ms )

The output will be written to stdout, but can be redirected to a file using `stdbuf -oL build/srv-scan 256 22 1000 &> "filename"`

## License
All files within this repo are released under the GNU GPL V3 License as per the LICENSE file stored in the root of this repo.
