dcmon
=====

A log viewer for docker-compose.

dcmon monitors the status and logs for containers managed by docker-compose. Each container's logs are displayed in a
separate tab in realtime. Log entries are automatically collapsed based on indentation for easier browsing. dcmon also
offers quick start, stop, and restart commands for monitored containers.


Building
--------

### Dependencies

* Docker
* docker-compose
* Qt (5.12 has been tested, other versions may work)
* Lua 5.3 (optional)

### Build instructions

```sh
qmake  # optionally, see qmake options below
make
```

To create a macOS distributable disk image after compiling:
```sh
macdeployqt dcmon.app -dmg
```

### qmake options

The build can be configured by adding flags to the `qmake` command line.

* To enable experimental/incomplete Lua support, add `USE_LUA=1`.
* To make a debug build, add `DEBUG=1`.


Running
-------

On Windows and Linux, invoke `dcmon` with the path to your `docker-compose.yml` or
`dcmon.lua` file, or launch it from the directory containing it.

On macOS, use `open /path/to/dcmon.app --args /path/to/docker-compose.yml`.

If launched without any parameters and no `docker-compose.yml` or `dcmon.lua` file
is found, then the last opened file will be used. If no file has been opened before,
or if the file could not be opened successfully, then dcmon will prompt the user
to choose a file.

### Keyboard shortcuts

On macOS, keyboard shortcuts use Command instead of Control.

* Ctrl+F: Opens the search bar. Use the search icon to toggle case-sensitivity and/or regular expressions.
* Ctrl+C: Copy selected log entries to the clipboard.


Configuration
-------------

If Lua support is enabled with the `USE_LUA=1` flag, then dcmon looks for a
`dcmon.lua` file in the same directory or a parent directory of the
`docker-compose.yml` file, or you may specify a `.lua` file instead of a `.yml` file.
This file is used for configuring dcmon's behavior for the associated project.

The following global variables are recognized:

* `yml`: If present, specifies an absolute or relative path to the corresponding
  `docker-compose.yml` file. If a `docker-compose.yml` was specified on the command
  line, then it is an error for this to refer to a different file.
* `containers`: A table specifying per-container configuration. The table keys are
  the container names (not the docker-compose service names) and the values are tables
  that may contain the following options:
  * `hide`: Boolean. If `true`, hides the container in the UI.
  * `filter`: Function. If present, the function will be called for each log line
    received. It will receive the line of text as a string parameter. If the function
    returns `nil` the line is suppressed. Otherwise, if it returns a string, that
    string will be emitted into the log.
* `views`: A table of filter views. The table key is the name of the filter view.
  The value is a function that takes the name of a container and a line of text.
  The function is called for every line logged by every container. If it returns a
  string, that string is appended to the filter view. Otherwise, the line is
  suppressed.


Roadmap
-------

In no particular order:

* Lua scripting support for status reporting.
* Desktop notifications for status changes and monitored keywords.
* Container status viewer.
* UI polish.
* Documentation.


License
-------

dcmon is copyright &copy; 2021 Flight Centre Travel Group.

dcmon is written and maintained by Adam Higerd (chighland@gmail.com).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
[GNU General Public License](LICENSE.md) for more details.
