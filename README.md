# Simple Arduino Http Server (SAHS)

Basic Arduino HTTP Server written in C++ for Arduino. As it's my first C++ project, it may seem a little messy (and/or wrong).

I try my best with memory management and parsing, but without STDLib it gets a little bit messy (no maps = sad panda)!

## Features

- [x] Simple request management with verbs (HTTPRequest)
- [ ] Header callback
- [x] Header max length
- [ ] Prevent Reads to take forever (leading DoS or parsing errors)
- [ ] Good HTTP protocol parse
- [ ] Simple response system (HTTPResponse)
